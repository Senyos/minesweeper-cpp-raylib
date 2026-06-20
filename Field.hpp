#pragma once

#include <memory>
#include <vector>

#include "Cell.hpp"

class Field {
    private:
        unsigned int                       length;
        unsigned int                       height;
        unsigned int                       bombs_amount;
        std::vector<std::shared_ptr<Cell>> cells;
        std::vector<unsigned int>          fog;
        bool                               is_game_over;

    public:
        Field(unsigned int length, unsigned int height, unsigned int bombs_amount);

        bool                               isGameOver()                const;
        unsigned int                       getLength()                 const;
        unsigned int                       getHeight()                 const;
        unsigned int                       getBombsAmount()            const;
        std::vector<std::shared_ptr<Cell>> getCells()                  const;
        size_t                             getCellsSize()              const;
        std::shared_ptr<Cell>              getCell(unsigned int index) const;
        // unsigned int                       getCursor()    const;

        void setGameOver(bool is_game_over);
        void setLength(unsigned int new_length);
        void setHeight(unsigned int new_height);

        void cellPush(std::shared_ptr<Cell> cell_ptr);

        void render(unsigned int screen_width, unsigned int screen_height) const;
        void input(unsigned int screen_width, unsigned int screen_height);
};
