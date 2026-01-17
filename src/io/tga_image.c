#include "tga_image.h"
#include <stdio.h>
#include "../render/color.h"

void write_tga_header(FILE* f, uint16_t width, uint16_t height)
{
    fwrite(&(uint8_t){0}, 1, 1, f);  // ID
    fwrite(&(uint8_t){0}, 1, 1, f);  // Color map
    fwrite(&(uint8_t){2}, 1, 1, f);  // Color mode
    // Color map zeroing
    fwrite(&(uint16_t){0}, 2, 1, f);
    fwrite(&(uint16_t){0}, 2, 1, f);
    fwrite(&(uint8_t){0}, 1, 1, f);
    // Image desc
    fwrite(&(uint16_t){0}, 2, 1, f);  // XOrigin
    fwrite(&(uint16_t){0}, 2, 1, f);  // YOrigin
    fwrite(&width, 2, 1, f);          // X
    fwrite(&height, 2, 1, f);         // Y

    fwrite(&(uint8_t){24}, 1, 1, f);  // Pixel depth
    fwrite(&(uint8_t){0}, 1, 1, f);   // Image Descriptor
}

void write_tga(const char* path, uint32_t* target, uint16_t width, uint16_t height)
{
    FILE* f = fopen(path, "wb");
    if (!f) return;
    write_tga_header(f, width, height);
    for (uint16_t y = 0; y < height; y++) {
        uint8_t row_buffer[width * 3];
        for (uint16_t x = 0; x < width; x++) {
            row_buffer[x * 3] = get_blue(target[y * width + x]);
            row_buffer[x * 3 + 1] = get_green(target[y * width + x]);
            row_buffer[x * 3 + 2] = get_red(target[y * width + x]);
        }
        fwrite(row_buffer, width * 3, 1, f);
    }
    fclose(f);
}

