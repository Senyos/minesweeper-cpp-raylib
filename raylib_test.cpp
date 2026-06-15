#include <iostream>
#include <memory>

#include "raylib-cpp.hpp"

class Cell {
    private:
        Vector2     position;
        float       scale;
        std::string value;
    public:
        void setValue(std::string value);

        std::string getValue() const;

        Cell(Vector2 position, float scale);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);
};

Cell::Cell(Vector2 position, float scale) : position(position), scale(scale), value(" ") {}

void Cell::setValue(std::string value) {
    this->value = value;
}

std::string Cell::getValue() const {
    return this->value;
}

void Cell::Draw() {
    float coef               = 0.8;
    float smaller_scale      = scale * coef;
    float even_smaller_scale = smaller_scale * coef;
    float move               = (scale - even_smaller_scale) / 2;
    float move_smaller       = (scale - even_smaller_scale) / 2;

    if (value == " ") {
        DrawRectangle(position.x,                position.y,                       scale,                     scale,              raylib::Color(100, 100, 100, 255));
        DrawRectangle(position.x + move,         position.y + move,                smaller_scale,             smaller_scale,      raylib::Color(120, 120, 120, 255));
        DrawRectangle(position.x + move_smaller, position.y + move_smaller,        even_smaller_scale,        even_smaller_scale, raylib::Color(140, 140, 140, 255));
        raylib::DrawText(value,                  position.x + move_smaller + move, position.y + move_smaller, smaller_scale,      raylib::Color(255, 255, 255, 255));
    } else {
        DrawRectangle(position.x,                position.y,                       scale,                     scale,              raylib::Color(100, 100, 100, 255));
        raylib::DrawText(value,                  position.x + move_smaller + move, position.y + move_smaller, smaller_scale,      raylib::Color(255, 255, 255, 255));
    }
}

bool Cell::isPressed(Vector2 mousePos, bool mousePressed) {   
    Rectangle rect = { position.x, position.y, scale, scale };
    if(CheckCollisionPointRec(mousePos,rect) && mousePressed) {
        return true;
    }
    return false;
}


class Field {
    private:
        unsigned int              length;
        unsigned int              height;
        unsigned int              cursor;
        std::vector<std::shared_ptr<Cell>>         cells;
        std::vector<unsigned int> fog;

    public:
        Field(unsigned int length, unsigned int height);

        unsigned int      getLength()                 const;
        unsigned int      getHeight()                 const;
        unsigned int      getCursor()                 const;
        std::vector<std::shared_ptr<Cell>> getCells()                  const;
        size_t            getCellsSize()              const;
        // Cell              getCell(unsigned int index) const;

        void setLength(unsigned int new_length);
        void setHeight(unsigned int new_height);

        void cellPush(std::shared_ptr<Cell> cell_ptr);

        void render() const;
        void input();
};

Field::Field(unsigned int length, unsigned int height) : length(length), height(height), cursor(0) {
    for (unsigned int l = 0; l < getLength(); ++l) {
        for (unsigned int h = 0; h < getHeight(); ++h) {
            cellPush( std::make_unique<Cell>( Cell((Vector2){ .x = (float)55*l, .y = (float)55*h }, 50) ) );
        }
    }
}

unsigned int     Field::getLength() const {
    return this->length;
}
unsigned int     Field::getHeight() const {
    return this->height;
}
unsigned int     Field::getCursor() const {
    return this->cursor;
}
std::vector<std::shared_ptr<Cell>> Field::getCells()  const {
    return std::vector<std::shared_ptr<Cell>>(this->cells);
}
size_t Field::getCellsSize()  const {
    return this->cells.size();
}
// Cell Field::getCell(unsigned int index)  const {
//     return this->cells.at(index);
// }

void Field::setLength(unsigned int new_length) {
    this->length = new_length;
}
void Field::setHeight(unsigned int new_height) {
    this->height = new_height;
}

void Field::cellPush(std::shared_ptr<Cell> cell_ptr) {
    this->cells.push_back(std::move(cell_ptr));
}

void Field::render() const {
    for (auto v : getCells()) {
        v->Draw();
    }
}
void Field::input() {
    for (auto v : getCells()) {
        if (v->isPressed(GetMousePosition(), IsMouseButtonDown(0))) {
            if (v->getValue() == " ")
                v->setValue("O");
        }
    }
}

int main() {
    int screenWidth = 640;
    int screenHeight = 800;

    raylib::Window window(screenWidth, screenHeight, "minesweeper");
    std::vector<std::shared_ptr<Cell>> cells;

    Field field = Field(10, 10);

    SetTargetFPS(60);
    while (!window.ShouldClose()) {
        BeginDrawing();

        field.render();
        field.input();

        window.ClearBackground(raylib::Color::LightGray());

        // raylib::DrawText("Congrats! You created your first window!", 190, 200, 20, raylib::Color::LightGray());

        EndDrawing();
    }

    return 0;
}
