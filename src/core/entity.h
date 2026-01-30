#pragma once
#include "../assets/model.h"

typedef struct {
    model* _model;
    transform _transform;
} entity;

entity create_entity(model* model);