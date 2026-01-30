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

//Transform

typedef struct {
	vec3f scale;
	vec3f translate;
} transform;

transform transform_identity(void);

vec3f apply_transform(vec3f point, transform _transform);