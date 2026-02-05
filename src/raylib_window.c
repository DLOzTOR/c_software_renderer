#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "renderer.h"
#include "../render/color.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "c_software_renderer");
    render_target* target = create_render_target(screenWidth, screenHeight);
    uint32_t color = create_color(0, 0, 0);
    for (int i = 0; i < target->width * target->height; i++) target->data[i] = color;

    entity monke = create_entity(load_model_obj("assets/monkey.obj"));
    monke._transform.scale = (vec3f){0.5f, 0.5f, 0.5f};
    color = create_color(255, 255, 255);
    draw_entity(&monke, target, color);
    monke._transform.rotation = quaternion_from_euler((vec3f){0, PI/8, 0});

    Image img ={
        .data = target->data,
        .width = target->width,
        .height = target->height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };

    Texture2D texture = LoadTextureFromImage(img);

    Vector2 v = {0, 0};
    Rectangle r = {target->width, target->height, target->width * 2, target->height * 2};
    float speed = 1.f;
    float ang = 0;

    while (!WindowShouldClose()) {
        reset_target(target);
        draw_entity(&monke, target, color);
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateTexture(texture, target->data);
        DrawTexturePro(texture,r,r, v, 180, WHITE);
        EndDrawing();
        printf("%f\n", GetFrameTime());
        monke._transform.translate.x += speed * GetFrameTime();
        ang += abs(speed) * GetFrameTime();
        monke._transform.rotation = quaternion_from_euler((vec3f){ang, ang, 0});
        if (fabs(monke._transform.translate.x) > 0.5) {
            speed *=-1;
        }
    }

    UnloadTexture(texture);
    free_model(monke._model);
    monke._model = (void*)0;
    free(target->data);
    CloseWindow();
    return 0;
}