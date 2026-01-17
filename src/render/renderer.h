#pragma once
#include "../math/math.h"

typedef struct {
    uint32_t* data;
    uint16_t width;
    uint16_t height;
} render_target;

render_target* create_render_target(uint16_t width, uint16_t height);
void draw_line(vec2i* start, vec2i* end, render_target* target, int color);