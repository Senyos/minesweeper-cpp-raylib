#include "Menu.hpp"

Menu::Menu(unsigned int length, unsigned int height) : length(length), height(height) {
    for (unsigned int l = 0; l < getLength(); ++l) {
        for (unsigned int h = 0; h < getHeight(); ++h) {
            buttonPush( std::make_unique<Button>( Button((Vector2){ .x = (float)450*l, .y = (float)200*h }, 400, 150) ) );
        }
    }
}

unsigned int Menu::getLength() const {
    return this->length;
}
unsigned int Menu::getHeight() const {
    return this->height;
}
std::vector<std::shared_ptr<Button>> Menu::getButtons()  const {
    return std::vector<std::shared_ptr<Button>>(this->buttons);
}
size_t Menu::getButtonsSize()  const {
    return this->buttons.size();
}
std::shared_ptr<Button> Menu::getButton(unsigned int index)  const {
    if (index >= getButtonsSize()) return nullptr;
    return this->buttons.at(index);
}


void Menu::buttonPush(std::shared_ptr<Button> button_ptr) {
    this->buttons.push_back(std::move(button_ptr));
}

void Menu::render(unsigned int screen_width, unsigned int screen_height) const {
    for (auto v : getButtons()) {
        v->Draw(screen_width, screen_height, getLength(), getHeight());
    }
}
void Menu::input(unsigned int screen_width, unsigned int screen_height) {
    for (unsigned int i = 0, e = getButtonsSize(); i < e; ++i) {
        std::shared_ptr<Button> button = getButton(i);

        if (button->isPressed(GetMousePosition(), IsMouseButtonPressed(0), screen_width, screen_height, getLength(), getHeight())) {
            if (button->getState() == false) button->press();
        } else if (IsMouseButtonReleased(0)) {
            if (button->getState() == true) button->unPress();
        }
    }
}
