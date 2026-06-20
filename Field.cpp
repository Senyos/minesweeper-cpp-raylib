#include <random>
// #include <iostream>

#include "Field.hpp"

Field::Field(unsigned int length, unsigned int height, unsigned int bombs_amount) : length(length), height(height), bombs_amount(bombs_amount), is_game_over(false) {
    for (unsigned int h = 0; h < getHeight(); ++h) {
        for (unsigned int l = 0; l < getLength(); ++l) {
            cellPush( std::make_unique<Cell>( Cell((Vector2){ .x = (float)55*l, .y = (float)55*h }, 50) ) );
        }
    }

    std::random_device rd; // non-deterministic generator
    std::mt19937 gen(rd()); // to seed mersenne twister
    std::uniform_int_distribution<> dist(1, 1000); // range from 1 to 100
    unsigned int bombs_setted = 0;
    for (unsigned int i = 0, e = getCellsSize(); i < e; ++i) {
        if (bombs_setted == getBombsAmount()) return;
        unsigned int randomNum = dist(gen);
        if (randomNum == 100) {
            bombs_setted += 1;
            getCell(i)->setTextUnder("*");
        }
        if (i == e - 1) i = 0;
    }
}

bool Field::isGameOver() const {
    return this->is_game_over;
}
unsigned int     Field::getLength() const {
    return this->length;
}
unsigned int     Field::getHeight() const {
    return this->height;
}
unsigned int     Field::getBombsAmount() const {
    return this->bombs_amount;
}
// unsigned int     Field::getCursor() const {
//     return this->cursor;
// }
std::vector<std::shared_ptr<Cell>> Field::getCells()  const {
    return std::vector<std::shared_ptr<Cell>>(this->cells);
}
size_t Field::getCellsSize()  const {
    return this->cells.size();
}
std::shared_ptr<Cell> Field::getCell(int index)  const {
    if (index < 0)                    return nullptr;
    if (index >= (int)getCellsSize()) return nullptr;
    return this->cells[index];
}

void Field::setGameOver(bool is_game_over) {
    this->is_game_over = is_game_over;
}
void Field::setLength(unsigned int new_length) {
    this->length = new_length;
}
void Field::setHeight(unsigned int new_height) {
    this->height = new_height;
}

void Field::cellPush(std::shared_ptr<Cell> cell_ptr) {
    this->cells.push_back(std::move(cell_ptr));
}

void Field::render(unsigned int screen_width, unsigned int screen_height) const {
    for (auto v : getCells()) {
        v->Draw(screen_width, screen_height, getLength(), getHeight());
    }
}
void Field::input(unsigned int screen_width, unsigned int screen_height) {
    for (unsigned int i = 0, e = getCellsSize(); i < e; ++i) {
        std::shared_ptr<Cell> cell = getCell(i);

        if ((cell->isPressed(GetMousePosition(), IsMouseButtonPressed(0), screen_width, screen_height, getLength(), getHeight())) && (cell->getTextAbove() != "#")) {
            if (cell->isHidden()) cell->show();
            if (cell->getTextUnder() == "*") setGameOver(true);
        } else if (cell->isPressed(GetMousePosition(), IsMouseButtonPressed(1), screen_width, screen_height, getLength(), getHeight())) {
            if (cell->getTextAbove() != "#") cell->setTextAbove("#");
            else cell->setTextAbove("");
        }

        std::shared_ptr<Cell> cell_left       = getCell(i - 1);
        std::shared_ptr<Cell> cell_right      = getCell(i + 1);
        std::shared_ptr<Cell> cell_above      = getCell(i - getLength());
        std::shared_ptr<Cell> cell_below      = getCell(i + getLength());

        std::shared_ptr<Cell> cell_up_left    = getCell(i - getLength() - 1);
        std::shared_ptr<Cell> cell_up_right   = getCell(i - getLength() + 1);
        std::shared_ptr<Cell> cell_down_left  = getCell(i + getLength() - 1);
        std::shared_ptr<Cell> cell_down_right = getCell(i + getLength() + 1);

        if (i%getLength() == 0) {
            cell_left = nullptr;
            cell_up_left  = nullptr;
            cell_down_left  = nullptr;
        }
        if (i%getLength() == getLength() - 1) {
            cell_right = nullptr;
            cell_up_right = nullptr;
            cell_down_right = nullptr;
        }
        if (i < getLength()) {
            cell_above    = nullptr;
            cell_up_left  = nullptr;
            cell_up_right = nullptr;
        }
        if ((i < (getLength()*getHeight())) && (i > (getLength()*getHeight() - getLength() - 1))) {
            cell_below      = nullptr;
            cell_down_left  = nullptr;
            cell_down_right = nullptr;
        }

        int count = 0;
        if ((cell_left)       && (cell_left->getTextUnder()       == "*")) ++count;
        if ((cell_right)      && (cell_right->getTextUnder()      == "*")) ++count;
        if ((cell_above)      && (cell_above->getTextUnder()      == "*")) ++count;
        if ((cell_below)      && (cell_below->getTextUnder()      == "*")) ++count;
        if ((cell_up_left)    && (cell_up_left->getTextUnder()    == "*")) ++count;
        if ((cell_up_right)   && (cell_up_right->getTextUnder()   == "*")) ++count;
        if ((cell_down_left)  && (cell_down_left->getTextUnder()  == "*")) ++count;
        if ((cell_down_right) && (cell_down_right->getTextUnder() == "*")) ++count;

        if (cell->getTextUnder() != "*") {
            if (count == 0) cell->setTextUnder("");
            else cell->setTextUnder(std::to_string(count));
        }

        if ( ((cell_left)  && (!cell_left->isHidden())  && cell_left->getTextUnder()  == "") ||
             ((cell_right) && (!cell_right->isHidden()) && cell_right->getTextUnder() == "") ||
             ((cell_above) && (!cell_above->isHidden()) && cell_above->getTextUnder() == "") ||
             ((cell_below) && (!cell_below->isHidden()) && cell_below->getTextUnder() == "") ||

             ((cell_up_left)    && (!cell_up_left->isHidden())    && cell_up_left->getTextUnder()    == "") ||
             ((cell_up_right)   && (!cell_up_right->isHidden())   && cell_up_right->getTextUnder()   == "") ||
             ((cell_down_left)  && (!cell_down_left->isHidden())  && cell_down_left->getTextUnder()  == "") ||
             ((cell_down_right) && (!cell_down_right->isHidden()) && cell_down_right->getTextUnder() == "")
           ) {
            if (cell->getTextUnder() != "*")
                cell->show();
        }
    }
}
