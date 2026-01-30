#include "renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/utils.h"

//Render target

render_target *create_render_target(uint16_t width, uint16_t height) {
    render_target *target = malloc(sizeof(render_target));
    if (!target)return 0;
    target->data = calloc(width * height, 4);
    target->width = width;
    target->height = height;
    target->aspect = (float)width/(float)height;
    return target;
}

void reset_target(render_target *target) {
    memset(target->data, 0, target->height * target->width * sizeof(*target->data));
}

//Render

void draw_line(vec2i *start, vec2i *end, render_target *target, int32_t color) {
    int d_x = end->x - start->x;
    int d_y = end->y - start->y;
    if (abs(abs(d_y) < abs(d_x))) {
        if (d_x < 0) {
            swap_p(start, end);
            d_x = end->x - start->x;
        }
        d_y = abs(end->y - start->y);
        int err = 0;
        int delta_err = 2 * d_y;
        int step = end->y > start->y ? 1 : -1;
        int row = start->y * target->width;
        int row_step = step * target->width;
        for (int x = start->x; x <= end->x; x++) {
            target->data[row + x] = color;
            err += delta_err;
            if (err >= d_x) {
                row += row_step;
                err -= d_x * 2;
            }
        }
    } else {
        if (d_y < 0) {
            swap_p(start, end);
            d_y = end->y - start->y;
        }
        d_x = abs(end->x - start->x);
        int err = 0;
        int delta_err = 2 * d_x;
        int x = start->x;
        int step = end->x > start->x ? 1 : -1;
        int row = start->y * target->width;
        for (int y = start->y; y <= end->y; y++) {
            target->data[row + x] = color;
            err += delta_err;
            if (err >= d_y) {
                x += step;
                err -= d_y * 2;
            }
            row += target->width;
        }
    }
}

void draw_wired_face(vec3f v1, vec3f v2, vec3f v3, render_target *target, int32_t color) {
    vec2i vi1 = vec3f_to_screen(v1, target->width, target->height, target->aspect);
    vec2i vi2 = vec3f_to_screen(v2, target->width, target->height, target->aspect);
    vec2i vi3 = vec3f_to_screen(v3, target->width, target->height, target->aspect);
    vec2i p1 = vi1;
    vec2i p2 = vi2;
    if (trim_line_to_screen(&p1, &p2, target->width, target->height)) {
        draw_line(&p1, &p2, target, color);
    }
    p1 = vi1;
    p2 = vi3;
    if (trim_line_to_screen(&p1, &p2, target->width, target->height)) {
        draw_line(&p1, &p2, target, color);
    }
    p1 = vi2;
    p2 = vi3;
    if (trim_line_to_screen(&p1, &p2, target->width, target->height)) {
        draw_line(&p1, &p2, target, color);
    }
}

void draw_wired_model(model *_model, transform* _transform, render_target *target, int32_t color) {
    for (int i = 0; i < _model->length; i += 3) {
        draw_wired_face(
            apply_transform(_model->tris[i], *_transform),
            apply_transform(_model->tris[i + 1], *_transform),
            apply_transform(_model->tris[i + 2], *_transform),
            target,
            color
        );
    }
}

void draw_entity(entity* _entity, render_target* target, int32_t color) {
    draw_wired_model(_entity->_model, &_entity->_transform, target, color);
}

