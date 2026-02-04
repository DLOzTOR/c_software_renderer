#pragma once
#include <stdint.h>
static const uint8_t A_SHIFT = 24;
static const uint8_t R_SHIFT = 0;
static const uint8_t G_SHIFT = 8;
static const uint8_t B_SHIFT = 16;
static const unsigned int MASK = 0xFF;

uint32_t create_color(uint8_t red, uint8_t green, uint8_t blue);

#define get_red(color) ((uint8_t)((color >> R_SHIFT) & MASK))
#define get_green(color) ((uint8_t)((color >> G_SHIFT) & MASK))
#define get_blue(color) ((uint8_t)((color >> B_SHIFT) & MASK))

