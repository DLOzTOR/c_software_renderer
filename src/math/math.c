#include "math.h"
vec2i vec3f_to_screen(vec3f v, int16_t width, int16_t height) {
    return (vec2i){
        (int32_t)(width * (v.x + 1) / 2),
        (int32_t)(height * (v.y + 1) / 2)
    };
}