#include "Cell.hpp"

Cell::Cell(Vector2 position, float scale) : position(position), scale(scale), is_hidden(true), text_above(""), text_under("") {}

void Cell::setTextUnder(std::string text) {
    this->text_under = text;
}
void Cell::setTextAbove(std::string text) {
    this->text_above = text;
}
void Cell::show() {
    this->is_hidden = false;
}

std::string Cell::getTextUnder() const {
    return this->text_under;
}
std::string Cell::getTextAbove() const {
    return this->text_above;
}
bool Cell::isHidden() const {
    return this->is_hidden;
}

void Cell::Draw(unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height) {
    float centered_x         = position.x + ((screen_width  - field_length*scale) / 2);
    float centered_y         = position.y + ((screen_height - field_height*scale) / 2);
    float coef               = 0.8;
    float smaller_scale      = scale * coef;
    float even_smaller_scale = smaller_scale * coef;
    float move               = (scale - even_smaller_scale) / 2;
    float move_smaller       = (scale - even_smaller_scale) / 2;

    if (isHidden()) {
        DrawRectangle(centered_x,                centered_y,                       scale,                     scale,              raylib::Color(100, 100, 100, 255));
        DrawRectangle(centered_x + move,         centered_y + move,                smaller_scale,             smaller_scale,      raylib::Color(120, 120, 120, 255));
        DrawRectangle(centered_x + move_smaller, centered_y + move_smaller,        even_smaller_scale,        even_smaller_scale, raylib::Color(140, 140, 140, 255));
        raylib::DrawText(text_above,             centered_x + move_smaller + move, centered_y + move_smaller, smaller_scale,      raylib::Color(255, 255, 255, 255));
    } else {
        if (getTextUnder() == "*") {
            DrawRectangle(centered_x,                centered_y,                       scale,                     scale,              raylib::Color(200, 100, 100, 255));
            raylib::DrawText(text_under,             centered_x + move_smaller + move, centered_y + move_smaller, smaller_scale,      raylib::Color(255, 255, 255, 255));
        } else {
            DrawRectangle(centered_x,                centered_y,                       scale,                     scale,              raylib::Color(100, 100, 100, 255));
            raylib::DrawText(text_under,             centered_x + move_smaller + move, centered_y + move_smaller, smaller_scale,      raylib::Color(255, 255, 255, 255));
        }
    }
}

bool Cell::isPressed(Vector2 mouse_pos, bool mouse_pressed, unsigned int screen_width, unsigned int screen_height, unsigned int field_length, unsigned int field_height) {   
    float centered_x = position.x + ((screen_width  - field_length*scale) / 2);
    float centered_y = position.y + ((screen_height - field_height*scale) / 2);
    Rectangle rect = { centered_x, centered_y, scale, scale };
    if(CheckCollisionPointRec(mouse_pos, rect) && mouse_pressed) {
        return true;
    }
    return false;
}
