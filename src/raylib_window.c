#include <stdlib.h>

#include "raylib.h"
#include "renderer.h"
#include "../render/color.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "c_software_renderer");
    render_target* rt = create_render_target(screenWidth, screenHeight);
    uint32_t color = create_color(0, 0, 0);
    for (int i = 0; i < rt->width * rt->height; i++) rt->data[i] = color;

    entity monke = create_entity(load_model_obj("assets/monkey.obj"));
    monke._transform.scale = (vec3f){0.7f, 0.7f, 0.7f};
    draw_entity(&monke, rt, create_color(255, 255, 255));
    free_model(monke._model);
    monke._model = (void*)0;
    Image img ={
        .data = rt->data,
        .width = rt->width,
        .height = rt->height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };

    Texture2D texture = LoadTextureFromImage(img);
    SetTargetFPS(60);
    Vector2 v = {0, 0};
    Rectangle r = {rt->width, rt->height, rt->width * 2, rt->height * 2};
    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawTexturePro(texture,r,r, v, 180, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);

    free(rt->data);
    CloseWindow();
    return 0;
}