#pragma once

#include "raylib-cpp.hpp"


class Cell {
    private:
        Vector2     position;
        float       scale;
        bool        is_hidden;
        std::string text_above;
        std::string text_under;
    public:
        Cell(Vector2 position, float scale);

        void setTextUnder(std::string text);
        void setTextAbove(std::string text);
        void show();

        std::string getTextUnder() const;
        std::string getTextAbove() const;
        bool        isHidden()     const;

        void Draw(unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height);
        bool isPressed(Vector2 mouse_pos, bool mouse_pressed, unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height);
};
