#include "raylib-cpp.hpp"

#include "Cell.hpp"
#include "Field.hpp"


#define INITIAL_CAMERA_ZOOM 1.0f


int main() {
    int screenWidth = 1280;
    int screenHeight = 960;

    raylib::Window window(screenWidth, screenHeight, "minesweeper");

    Field field = Field(15, 15, 25);

    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    raylib::RenderTexture2D renderTexture(screenWidth, screenHeight);

    raylib::Camera2D camera;
    camera.zoom   = INITIAL_CAMERA_ZOOM;
    camera.offset = (Vector2){0.0f, 0.0f};
    camera.target = (Vector2){0.0f, 0.0f};


    while (!window.ShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
            return 0;
        }

        BeginTextureMode(renderTexture);
            field.render();
        EndTextureMode();

        BeginDrawing();
        BeginMode2D(camera);

            DrawTexturePro(renderTexture.texture,
                    (Rectangle) {
                    .x = 0,
                    .y = 0,
                    .width  = static_cast<float>(renderTexture.texture.width),
                    .height = static_cast<float>(-renderTexture.texture.height),
                    },
                    (Rectangle) {
                    .x = static_cast<float>((GetScreenWidth() - GetScreenHeight()*1.3333333333333333)/2),
                    .y = 0,
                    .width  = static_cast<float>(GetScreenHeight()*1.3333333333333333),
                    .height = static_cast<float>(GetScreenHeight()),
                    },
                    (Vector2) { 
                    .x = 0,
                    .y = 0,
                    },
                    0.0f,
                    WHITE);


            window.ClearBackground(raylib::Color::LightGray());

        // raylib::DrawText("Congrats! You created your first window!", 190, 200, 20, raylib::Color::LightGray());
        EndMode2D();
        EndDrawing();

        field.input();
    }

    return 0;
}
