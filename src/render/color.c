#include "color.h"
uint32_t create_color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)red << R_SHIFT) | ((uint32_t)green << G_SHIFT) | ((uint32_t)blue << B_SHIFT);
}
