#include "model.h"
#include <stdlib.h>
void free_model(model* _model) {
    free(_model->tris);
    free(_model);
}