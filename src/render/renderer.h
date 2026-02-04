#pragma once
#include "../assets/model.h"
#include "../math/math_ext.h"
#include  "../core/entity.h"

typedef struct {
    uint32_t* data;
    uint16_t width;
    uint16_t height;
    float aspect;
} render_target;

render_target* create_render_target(uint16_t width, uint16_t height);
void reset_target(render_target* target);

void draw_line(vec2i* start, vec2i* end, render_target* target, int32_t color);
void draw_wired_face(vec3f v1, vec3f v2, vec3f v3, render_target* target, int32_t color);
void draw_wired_model(model* _model, transform* _transform, render_target* target, int32_t color);
void draw_entity(entity* _entity, render_target* target, int32_t color);