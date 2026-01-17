#pragma once
#include "../math/math.h"

typedef struct {
    vec3f* tris;
    uint32_t length;
} model;

void free_model(model* _model);