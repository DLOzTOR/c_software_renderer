#pragma once
#include <stdint.h>

typedef struct{
	int32_t x;
	int32_t y;
} vec2i;

typedef struct {
	float x;
	float y;
	float z;
} vec3f;

vec2i vec3f_to_screen(vec3f v, int16_t width, int16_t height);