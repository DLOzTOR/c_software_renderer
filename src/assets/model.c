#include "model.h"
#include <stdlib.h>
#include <stdio.h>
void free_model(model* _model) {
    free(_model->tris);
    free(_model);
}

model* load_model_obj(const char* path) {
    FILE* _file = fopen(path,"r");
    if (!_file) {
        return NULL;
    }
    uint32_t vertices_count = 0;
    uint32_t faces_count = 0;
    char line[512];
    while (fgets(line, sizeof(line), _file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            vertices_count++;
        }
        else if (line[0] == 'f') {
            faces_count++;
        }
    }
    rewind(_file);
    model* loaded_model = malloc(sizeof(model));
    loaded_model->tris = calloc(faces_count * 3, sizeof(vec3f));
    loaded_model->length = faces_count * 3;
    vec3f* vertices = calloc(vertices_count, sizeof(vec3f));
    int vertices_readed = 0;
    int faces_readed = 0;
    vec3f* faces = loaded_model->tris;
    while (fgets(line, sizeof(line), _file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            vec3f* v = &vertices[vertices_readed++];
            sscanf(line, "v %f %f %f", &v->x, &v->y, &v->z);
        }
        else if (line[0] == 'f') {
            int v1, v2, v3;
            sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v1, &v2, &v3);
            faces[faces_readed * 3] = vertices[v1 - 1];
            faces[faces_readed * 3+ 1] = vertices[v2 - 1];
            faces[faces_readed * 3+ 2] = vertices[v3 - 1];
            faces_readed++;
        }
    }
    printf("%d", vertices_count);
    printf("%d", faces_count);
    fclose(_file);
    free(vertices);
    return loaded_model;
}