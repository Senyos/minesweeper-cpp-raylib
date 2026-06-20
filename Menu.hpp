#pragma once

#include <memory>
#include <vector>

#include "Button.hpp"

class Menu {
    private:
        unsigned int                         length;
        unsigned int                         height;
        std::vector<std::shared_ptr<Button>> buttons;

    public:
        Menu(unsigned int length, unsigned int height);

        unsigned int                         getLength()                   const;
        unsigned int                         getHeight()                   const;
        std::vector<std::shared_ptr<Button>> getButtons()                  const;
        size_t                               getButtonsSize()              const;
        std::shared_ptr<Button>              getButton(unsigned int index) const;

        void buttonPush(std::shared_ptr<Button> button_ptr);

        void render(unsigned int screen_width, unsigned int screen_height) const;
        void input(unsigned int screen_width, unsigned int screen_height);
};
