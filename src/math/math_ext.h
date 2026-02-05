#pragma once
#include <stdbool.h>
#include <stdint.h>


//Vectors

typedef struct{
	int32_t x;
	int32_t y;
} vec2i;

typedef struct {
	float x;
	float y;
	float z;
} vec3f;

vec2i vec3f_to_screen(vec3f v, uint16_t width, uint16_t height, float aspect);

vec2i vec2i_screen_normalize(vec2i v, uint16_t width, uint16_t height);

bool trim_line_to_screen(vec2i* p1, vec2i* p2, uint16_t width, uint16_t height);

//Matrices

typedef struct {
	float data[16];
} mat4x4;

mat4x4 mat4x4_identity();

mat4x4 mat4x4_mult(mat4x4 a, mat4x4 b);

//Quaternion

typedef struct {
	float w;
	float x;
	float y;
	float z;
} quaternion;

quaternion quaternion_conjugate(quaternion a);

quaternion quaternion_multiply(quaternion a, quaternion b);

quaternion quaternion_from_axis_angle(vec3f axis, float angle);

quaternion quaternion_from_euler(vec3f rotation);

vec3f vec3f_apply_rotation(vec3f v, quaternion a, quaternion a_conjugate);

//Transform

typedef struct {
	vec3f scale;
	vec3f translate;
	quaternion rotation;
} transform;

transform transform_identity(void);

vec3f apply_transform(vec3f point, transform _transform, quaternion rot_conjugate);