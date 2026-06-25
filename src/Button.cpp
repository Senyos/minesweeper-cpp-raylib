#include "Button.hpp"

Button::Button(Vector2 position, float width, float height) : position(position), width(width), height(height), text(""), is_pressed(false) {}

void Button::setText(std::string text) {
    this->text = text;
}
void Button::press() {
    this->is_pressed = true;
}
void Button::unPress() {
    this->is_pressed = false;
}

bool Button::getState() const {
    return this->is_pressed;
}
std::string Button::getText() const {
    return this->text;
}

void Button::Draw(unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height) {
    float centered_x          = position.x + ((screen_width  - field_length*(width)) / 2);
    float centered_y          = position.y + ((screen_height - field_height*(height)) / 2);
    float coef                = 0.8;
    float smaller_width       = width  * coef;
    float smaller_height      = height * coef;
    float even_smaller_width  = smaller_width  * coef;
    float even_smaller_height = smaller_height * coef;
    float move_width          = (width  - even_smaller_width)  / 2;
    float move_height         = (height - even_smaller_height) / 2;
    float move_smaller_width  = (width  - even_smaller_width)  / 2;
    float move_smaller_height = (height - even_smaller_height) / 2;

    if (getState() == false) {
        DrawRectangle(centered_x, centered_y, width, height, raylib::Color(100, 100, 100, 255));
        DrawRectangle(centered_x + move_width, centered_y + move_height, smaller_width, smaller_height, raylib::Color(120, 120, 120, 255));
        DrawRectangle(centered_x + move_smaller_width, centered_y + move_smaller_height, even_smaller_width, even_smaller_height, raylib::Color(140, 140, 140, 255));
        raylib::DrawText(text, centered_x + move_width/2, centered_y + move_smaller_height, smaller_height/2, raylib::Color(0, 0, 0, 255));
    } else {
        DrawRectangle(centered_x, centered_y, width, height, raylib::Color(100, 100, 100, 255));
        raylib::DrawText(text, centered_x + move_width/2, centered_y + move_smaller_height, smaller_height/2, raylib::Color(255, 255, 255, 255));
    }
}

bool Button::isPressed(Vector2 mouse_pos, bool mouse_pressed, unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height) {
    float centered_x = position.x + ((screen_width  - field_length*(width))  / 2);
    float centered_y = position.y + ((screen_height - field_height*(height)) / 2);
    Rectangle rect = { centered_x, centered_y, width, height };
    if(CheckCollisionPointRec(mouse_pos, rect) && mouse_pressed) {
        return true;
    }
    return false;
}
