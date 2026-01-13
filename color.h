#pragma once
typedef unsigned char uchar;
const uchar R_SHIFT = 16;
const uchar G_SHIFT = 8;
const uchar B_SHIFT = 0;
const unsigned int MASK = 0xFF;

int create_color(uchar red, uchar green, uchar blue)
{
    return (red << R_SHIFT) | (green << G_SHIFT) | (blue << B_SHIFT);
}

uchar get_red(int color) { return (uchar)((color >> R_SHIFT) & MASK); }
uchar get_green(int color) { return (uchar)((color >> G_SHIFT) & MASK); }
uchar get_blue(int color) { return (uchar)((color >> B_SHIFT) & MASK); }
