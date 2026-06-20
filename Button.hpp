#pragma once

#include "raylib-cpp.hpp"


class Button {
    private:
        Vector2     position;
        float       width;
        float       height;
        std::string text;
        bool        is_pressed;
    public:
        Button(Vector2 position, float width, float height);

        void press();
        void unPress();
        void setText(std::string text);
        void show();

        bool        getState()  const;
        std::string getText()   const;
        bool        isPressed() const;

        void Draw(unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height);
        bool isPressed(Vector2 mouse_pos, bool mouse_pressed, unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height);
};
