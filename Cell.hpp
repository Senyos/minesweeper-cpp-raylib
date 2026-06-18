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
        void setTextUnder(std::string text);
        void setTextAbove(std::string text);
        void show();

        std::string getTextUnder() const;
        std::string getTextAbove() const;
        bool        isHidden()     const;

        Cell(Vector2 position, float scale);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);
};
