#pragma once
#include <stdint.h>
const uint8_t R_SHIFT = 16;
const uint8_t G_SHIFT = 8;
const uint8_t B_SHIFT = 0;
const unsigned int MASK = 0xFF;

uint32_t create_color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)red << R_SHIFT) | ((uint32_t)green << G_SHIFT) | ((uint32_t)blue << B_SHIFT);
}

#define get_red(color) ((uint8_t)((color >> R_SHIFT) & MASK))
#define get_green(color) ((uint8_t)((color >> G_SHIFT) & MASK))
#define get_blue(color) ((uint8_t)((color >> B_SHIFT) & MASK))

