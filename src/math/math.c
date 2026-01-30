#include "math.h"
#include <stdlib.h>

//Cohen–Sutherland

const uint8_t INSIDE = 0b0000;
const uint8_t LEFT   = 0b0001;
const uint8_t RIGHT  = 0b0010;
const uint8_t BOTTOM = 0b0100;
const uint8_t TOP    = 0b1000;

uint8_t get_point_position_code(int32_t x, int32_t y, uint16_t width, uint16_t height) {
    uint8_t code = 0;
    if (x < 0) {
        code |= LEFT;
    }
    else if (x > width - 1) {
        code |= RIGHT;
    }
    if (y < 0) {
        code |= BOTTOM;
    }
    else if (y > height - 1) {
        code |= TOP;
    }
    return code;
}

bool trim_line_to_screen(vec2i* p1, vec2i* p2, uint16_t width, uint16_t height){
    uint8_t code1 = get_point_position_code(p1->x, p1->y, width, height);
    uint8_t code2 = get_point_position_code(p2->x, p2->y, width, height);

    while (true) {
        if (!(code1 | code2)) return true;
        if (code1 & code2) return false;

        uint8_t cur = code1 ? code1 : code2;

        int32_t x = 0;
        int32_t y = 0;

        if (cur & TOP) {
            x = p1->x + (int32_t)((int64_t)(p2->x - p1->x) * (height - 1 - p1->y) / (p2->y - p1->y));
            y = height - 1;
        } else if (cur & BOTTOM) {
            x = p1->x + (int32_t)((int64_t)(p2->x - p1->x) * (-p1->y) / (p2->y - p1->y));
            y = 0;
        } else if (cur & RIGHT) {
            y = p1->y + (int32_t)((int64_t)(p2->y - p1->y) * (width - 1 - p1->x) / (p2->x - p1->x));
            x = width - 1;
        } else if (cur & LEFT) {
            y = p1->y + (int32_t)((int64_t)(p2->y - p1->y) * (-p1->x) / (p2->x - p1->x));
            x = 0;
        }
        if (cur == code1) {
            p1->x = x;
            p1->y = y;
            code1 = get_point_position_code(x, y, width, height);
        }
        else {
            p2->x = x;
            p2->y = y;
            code2 = get_point_position_code(x, y, width, height);
        }
    }
}

//Vectors

vec2i vec3f_to_screen(vec3f v, uint16_t width, uint16_t height) {
    return (vec2i){
        (int32_t)((float)width * v.x + (float) width) / 2,
        (int32_t)((float)height * v.y + (float) height) / 2
    };
}

vec2i vec2i_screen_normalize(vec2i v, uint16_t width, uint16_t height) {
    return (vec2i){
        v.x > width - 1 ? width - 1 : v.x < 0 ? 0 : v.x,
        v.y > height - 1 ? height - 1 : v.y < 0 ? 0 : v.y,
    };
}

//Transform

transform transform_identity(void) {
    return (transform){
        {1, 1, 1},
        {0, 0, 0}
    };
}

vec3f apply_transform(vec3f point, transform _transform) {
    return (vec3f){
        point.x * _transform.scale.x + _transform.translate.x,
        point.y * _transform.scale.y + _transform.translate.y,
        point.y * _transform.scale.y + _transform.translate.y
    };
}