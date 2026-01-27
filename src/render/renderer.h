#pragma once
#include "../assets/model.h"
#include "../math/math.h"

typedef struct {
    uint32_t* data;
    uint16_t width;
    uint16_t height;
} render_target;

render_target* create_render_target(uint16_t width, uint16_t height);
void draw_line(vec2i* start, vec2i* end, render_target* target, int color);
void draw_wired_face(vec3f* v1, vec3f* v2, vec3f* v3, render_target* target, int color);
void draw_wired_model(model* _model, render_target* target, int color);
void reset_target(render_target* target);