#include <iostream>

#include "raylib-cpp.hpp"

#include "Cell.hpp"
#include "Field.hpp"


#define INITIAL_CAMERA_ZOOM 1.0f


int main() {
    int screen_width = 1280;
    int screen_height = 960;

    raylib::Window window(screen_width, screen_height, "minesweeper");

    Field field = Field(15, 15, 25);

    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // raylib::RenderTexture2D renderTexture(screen_width, screen_height);

    raylib::Camera2D camera;
    camera.zoom   = INITIAL_CAMERA_ZOOM;
    camera.offset = (Vector2){0.0f, 0.0f};
    camera.target = (Vector2){0.0f, 0.0f};


    while (!window.ShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
            return 0;
        }
        while (field.isGameOver()) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
                return 0;
            }
            if (IsKeyPressed(KEY_R)) {
                field.setGameOver(false);
                break;
            }
            BeginDrawing();
            BeginMode2D(camera);
                field.render(GetScreenWidth(), GetScreenHeight());
                float centered_x = ((GetScreenWidth() - field.getLength()*55) / 2);
                float centered_y = ((GetScreenHeight() - field.getHeight()*55) / 2);
                raylib::DrawText("GAME OVER (press R to restart\nor ESC to return to the main menu)", centered_x + 2, centered_y + 2, 50, raylib::Color::Pink());
                raylib::DrawText("GAME OVER (press R to restart\nor ESC to return to the main menu)", centered_x, centered_y, 50, raylib::Color::Gold());
                window.ClearBackground(raylib::Color::LightGray());
            EndMode2D();
            EndDrawing();
        }

        // BeginTextureMode(renderTexture);
        // EndTextureMode();

        BeginDrawing();
        BeginMode2D(camera);

            field.render(GetScreenWidth(), GetScreenHeight());
            // DrawTexturePro(renderTexture.texture,
            //         (Rectangle) {
            //         .x = 0,
            //         .y = 0,
            //         .width  = static_cast<float>(renderTexture.texture.width),
            //         .height = static_cast<float>(-renderTexture.texture.height),
            //         },
            //         (Rectangle) {
            //         .x = static_cast<float>((GetScreenWidth() - GetScreenHeight()*1.3333333333333333)/2),
            //         .y = 0,
            //         .width  = static_cast<float>(GetScreenHeight()*1.3333333333333333),
            //         .height = static_cast<float>(GetScreenHeight()),
            //         },
            //         (Vector2) { 
            //         .x = 0,
            //         .y = 0,
            //         },
            //         0.0f,
            //         WHITE);


            window.ClearBackground(raylib::Color::LightGray());

        // raylib::DrawText("Congrats! You created your first window!", 190, 200, 20, raylib::Color::LightGray());
        EndMode2D();
        EndDrawing();

        field.input(GetScreenWidth(), GetScreenHeight());
    }

    return 0;
}
