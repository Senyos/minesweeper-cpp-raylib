// #include <iostream>

#include "raylib-cpp.hpp"

#include "Cell.hpp"
#include "Field.hpp"
#include "Button.hpp"
#include "Menu.hpp"


#define INITIAL_CAMERA_ZOOM 1.0f


int main() {
    int screen_width = 1280;
    int screen_height = 960;

    raylib::Window window(screen_width, screen_height, "minesweeper");

    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // raylib::RenderTexture2D renderTexture(screen_width, screen_height);

    raylib::Camera2D camera;
    camera.zoom   = INITIAL_CAMERA_ZOOM;
    camera.offset = (Vector2){0.0f, 0.0f};
    camera.target = (Vector2){0.0f, 0.0f};

    Menu menu = Menu(1, 3);
    menu.getButton(0)->setText("START");
    menu.getButton(1)->setText("FIELD:\n[10 x 10]");
    menu.getButton(2)->setText("EXIT (ESC)");

    bool game_started = false;

    unsigned int field_size = 10;
    unsigned int bombs_amount = field_size*field_size*0.20f; 
    Field field = Field(field_size, field_size, bombs_amount);

    while (!window.ShouldClose()) {
        if ((IsKeyPressed(KEY_ESCAPE)) && (game_started == false)) {
            CloseWindow();
            return 0;
        }


        if (game_started == false) {
            BeginDrawing();
            BeginMode2D(camera);
                menu.render(GetScreenWidth(), GetScreenHeight());
                window.ClearBackground(raylib::Color::LightGray());
            EndMode2D();
            EndDrawing();

            menu.input(GetScreenWidth(), GetScreenHeight());
        }

        if ((game_started == false) && (menu.getButton(2)->isPressed(GetMousePosition(), IsMouseButtonReleased(0), GetScreenWidth(), GetScreenHeight(), menu.getLength(), menu.getHeight()))) {
            CloseWindow();
            return 0;
        }

        if ((game_started == false) && (menu.getButton(1)->isPressed(GetMousePosition(), IsMouseButtonPressed(0), GetScreenWidth(), GetScreenHeight(), menu.getLength(), menu.getHeight()))) {
            if (field_size == 10) {
                field_size = 15;
                menu.getButton(1)->setText("FIELD:\n[15 x 15]");
            } else if (field_size == 15) {
                field_size = 20;
                menu.getButton(1)->setText("FIELD:\n[20 x 20]");
            } else if (field_size == 20) {
                field_size = 10;
                menu.getButton(1)->setText("FIELD:\n[10 x 10]");
            }
            bombs_amount = field_size*field_size*0.20f;
        }

        if ((game_started == false) && (menu.getButton(0)->isPressed(GetMousePosition(), IsMouseButtonReleased(0), GetScreenWidth(), GetScreenHeight(), menu.getLength(), menu.getHeight()))) game_started = true;

        if (game_started == false) field = Field(field_size, field_size, bombs_amount);

        while (game_started) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_started = false;
            }

            while (field.isGameOver()) {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    game_started = false;
                    break;
                }
                if (IsKeyPressed(KEY_R)) {
                    field = Field(field_size, field_size, bombs_amount);
                    break;
                }
                BeginDrawing();
                BeginMode2D(camera);
                    field.render(GetScreenWidth(), GetScreenHeight());
                    float centered_x = ((GetScreenWidth() - field.getLength()*55) / 2);
                    float centered_y = (GetScreenHeight() / 2);
                    raylib::DrawText("GAME OVER (press R to restart\nor ESC to return to the main menu)", centered_x + 2, centered_y + 2, 50, raylib::Color::Maroon());
                    raylib::DrawText("GAME OVER (press R to restart\nor ESC to return to the main menu)", centered_x, centered_y, 50, raylib::Color::Black());
                    window.ClearBackground(raylib::Color::LightGray());
                EndMode2D();
                EndDrawing();
            }

            while (field.isWin()) {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    game_started = false;
                    break;
                }
                if (IsKeyPressed(KEY_R)) {
                    field = Field(field_size, field_size, bombs_amount);
                    break;
                }
                BeginDrawing();
                BeginMode2D(camera);
                    field.render(GetScreenWidth(), GetScreenHeight());
                    float centered_x = ((GetScreenWidth() - field.getLength()*55) / 2);
                    float centered_y = (GetScreenHeight() / 2);
                    raylib::DrawText("YOU WON! (press R to restart\nor ESC to return to the main menu)", centered_x + 2, centered_y + 2, 50, raylib::Color::Green());
                    raylib::DrawText("YOU WON! (press R to restart\nor ESC to return to the main menu)", centered_x, centered_y, 50, raylib::Color::DarkGreen());
                    window.ClearBackground(raylib::Color::LightGray());
                EndMode2D();
                EndDrawing();
            }

            BeginDrawing();
            BeginMode2D(camera);
                field.render(GetScreenWidth(), GetScreenHeight());
                window.ClearBackground(raylib::Color::LightGray());
            EndMode2D();
            EndDrawing();

            field.input(GetScreenWidth(), GetScreenHeight());
        }
    }

    return 0;
}
