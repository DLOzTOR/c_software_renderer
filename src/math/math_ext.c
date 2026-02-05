#include <math.h>
#include "math_ext.h"
#include <stdlib.h>

//Cohen–Sutherland

const uint8_t INSIDE = 0b0000;
const uint8_t LEFT = 0b0001;
const uint8_t RIGHT = 0b0010;
const uint8_t BOTTOM = 0b0100;
const uint8_t TOP = 0b1000;

uint8_t get_point_position_code(int32_t x, int32_t y, uint16_t width, uint16_t height) {
    uint8_t code = 0;
    if (x < 0) {
        code |= LEFT;
    } else if (x > width - 1) {
        code |= RIGHT;
    }
    if (y < 0) {
        code |= BOTTOM;
    } else if (y > height - 1) {
        code |= TOP;
    }
    return code;
}

bool trim_line_to_screen(vec2i *p1, vec2i *p2, uint16_t width, uint16_t height) {
    uint8_t code1 = get_point_position_code(p1->x, p1->y, width, height);
    uint8_t code2 = get_point_position_code(p2->x, p2->y, width, height);

    while (true) {
        if (!(code1 | code2)) return true;
        if (code1 & code2) return false;

        uint8_t cur = code1 ? code1 : code2;

        int32_t x = 0;
        int32_t y = 0;

        if (cur & TOP) {
            x = p1->x + (int32_t) ((int64_t) (p2->x - p1->x) * (height - 1 - p1->y) / (p2->y - p1->y));
            y = height - 1;
        } else if (cur & BOTTOM) {
            x = p1->x + (int32_t) ((int64_t) (p2->x - p1->x) * (-p1->y) / (p2->y - p1->y));
            y = 0;
        } else if (cur & RIGHT) {
            y = p1->y + (int32_t) ((int64_t) (p2->y - p1->y) * (width - 1 - p1->x) / (p2->x - p1->x));
            x = width - 1;
        } else if (cur & LEFT) {
            y = p1->y + (int32_t) ((int64_t) (p2->y - p1->y) * (-p1->x) / (p2->x - p1->x));
            x = 0;
        }
        if (cur == code1) {
            p1->x = x;
            p1->y = y;
            code1 = get_point_position_code(x, y, width, height);
        } else {
            p2->x = x;
            p2->y = y;
            code2 = get_point_position_code(x, y, width, height);
        }
    }
}

//Vectors

vec2i vec3f_to_screen(vec3f v, uint16_t width, uint16_t height, float aspect) {
    return (vec2i){
        (int32_t) ((float) width * v.x / aspect + (float) width) / 2,
        (int32_t) ((float) height * v.y + (float) height) / 2
    };
}

vec2i vec2i_screen_normalize(vec2i v, uint16_t width, uint16_t height) {
    return (vec2i){
        v.x > width - 1 ? width - 1 : v.x < 0 ? 0 : v.x,
        v.y > height - 1 ? height - 1 : v.y < 0 ? 0 : v.y,
    };
}

//Matrices

mat4x4 mat4x4_identity() {
    return (mat4x4){{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }
    };
}

mat4x4 mat4x4_mult(mat4x4 a, mat4x4 b) {
    mat4x4 c;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            c.data[row * 4 + col] = 0.0f;
            for (int k = 0; k < 4; k++) {
                c.data[row * 4 + col] +=
                    a.data[row * 4 + k] * b.data[k * 4 + col];
            }
        }
    }
    return c;
}

//Quaternion

const vec3f OX = {1, 0,0};
const vec3f OY = {0, 1,0};
const vec3f OZ = {0, 0,1};

quaternion quaternion_conjugate(quaternion a) {
    return (quaternion){
        .w = a.w,
        .x = -a.x,
        .y = -a.y,
        .z = -a.z
    };
}

quaternion quaternion_normalize(quaternion a) {
    float len = sqrtf(a.w*a.w + a.x*a.x + a.y*a.y + a.z*a.z);
    if (len < 1e-6) {
        return (quaternion){1.0f, 0.0f, 0.0f, 0.0f};;
    }
    float inv_len = 1.0f / len;
    a.w *= inv_len;
    a.x *= inv_len;
    a.y *= inv_len;
    a.z *= inv_len;
    return a;
}

quaternion quaternion_multiply(quaternion a, quaternion b) {
    return (quaternion){
        .w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        .x = a.x * b.w + a.w * b.x + a.y * b.z - a.z * b.y,
        .y = a.w * b.y + a.y * b.w - a.x * b.z + a.z * b.x,
        .z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x
    };
}

quaternion quaternion_from_axis_angle(vec3f axis, float angle) {
    float half_angle = angle * 0.5f;
    float s = sin(half_angle);
    return (quaternion){
        .w = cos(half_angle),
        .x = s * axis.x,
        .y = s * axis.y,
        .z = s * axis.z
    };
}

quaternion quaternion_from_euler(vec3f rotation) {
    quaternion x = quaternion_from_axis_angle(OX, rotation.x);
    quaternion y = quaternion_from_axis_angle(OY, rotation.y);
    quaternion z = quaternion_from_axis_angle(OZ, rotation.z);
    return quaternion_normalize(quaternion_multiply(quaternion_multiply(y, x), z));
}

vec3f vec3f_apply_rotation(vec3f v, quaternion a, quaternion a_conjugate) {
    quaternion v_q = {0, v.x, v.y, v.z};
    quaternion result = quaternion_multiply(quaternion_multiply(a,v_q), a_conjugate);
    return (vec3f){
        result.x,
        result.y,
        result.z
    };
}

//Transform

transform transform_identity(void) {
    return (transform){
        {1, 1, 1},
        {0, 0, 0},
        {1, 0, 0, 0}
    };
}

vec3f apply_transform(vec3f point, transform _transform, quaternion rot_conjugate) {
    vec3f transformed = {
        point.x * _transform.scale.x,
        point.y * _transform.scale.y,
        point.z * _transform.scale.z
    };
    transformed = vec3f_apply_rotation(transformed, _transform.rotation,rot_conjugate);
    return (vec3f){
        transformed.x + _transform.translate.x,
        transformed.y + _transform.translate.y,
        transformed.z + _transform.translate.z
    };
}
