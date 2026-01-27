#include "math.h"

#include <stdlib.h>

vec2i vec3f_to_screen(vec3f v, uint16_t width, uint16_t height) {
    return (vec2i){
        (int32_t)((float)width * v.x + (float) width) / 2,
        (int32_t)((float)height * v.y + (float) height) / 2
    };
}

vec2i vec2i_screen_normalize(vec2i v, uint16_t width, uint16_t height) {
    return (vec2i){
        v.x > width - 1 ? width - 1 : v.x < 0 ? 0 : v.x,
        v.y > height - 1 ? height - 1 : v.y < 0 ? 0 : v.y,
    };
}