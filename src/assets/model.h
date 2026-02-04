#pragma once
#include "../math/math_ext.h"

typedef struct {
    vec3f* tris;
    uint32_t length;
} model;

void free_model(model* _model);
model* load_model_obj(const char* path);