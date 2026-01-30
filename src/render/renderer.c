#include "renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/utils.h"

render_target *create_render_target(uint16_t width, uint16_t height) {
    render_target *target = malloc(sizeof(render_target));
    if (!target)return 0;
    target->data = calloc(width * height, 4);
    target->width = width;
    target->height = height;
    return target;
}

void draw_line(vec2i *start, vec2i *end, render_target *target, int color) {
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

void draw_wired_face(vec3f *v1, vec3f *v2, vec3f *v3, render_target *target, int color) {
    vec2i vi1 = vec3f_to_screen(*v1, target->width, target->height);
    vec2i vi2 = vec3f_to_screen(*v2, target->width, target->height);
    vec2i vi3 = vec3f_to_screen(*v3, target->width, target->height);
    vec2i p1 = vi1;
    vec2i p2 = vi2;
    trim_line_to_screen(&p1, &p2, target->width, target->height);
    draw_line(&p1, &p2, target, color);
    p1 = vi1;
    p2 = vi3;
    trim_line_to_screen(&p1, &p2, target->width, target->height);
    draw_line(&p1, &p2, target, color);
    p1 = vi2;
    p2 = vi3;
    trim_line_to_screen(&p1, &p2, target->width, target->height);
    draw_line(&p1, &p2, target, color);
}

void draw_wired_model(model *_model, render_target *target, int color) {
    int faces = 0;
    for (int i = 0; i < _model->length; i += 3) {
        faces++;
        draw_wired_face(
            &_model->tris[i],
            &_model->tris[i + 1],
            &_model->tris[i + 2],
            target,
            color
        );
    }
    printf("%d\n", faces);
}

void reset_target(render_target *target) {
    memset(target->data, 0, target->height * target->width * sizeof(*target->data));
}
