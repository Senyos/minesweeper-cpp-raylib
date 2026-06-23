#pragma once

#include <memory>
#include <vector>

#include "Cell.hpp"

class Field {
    private:
        unsigned int                       length;
        unsigned int                       height;
        unsigned int                       cells_amount;
        unsigned int                       bombs_amount;
        std::vector<std::shared_ptr<Cell>> cells;
        bool                               is_game_over;
        bool                               is_win;

    public:
        Field(unsigned int length, unsigned int height, unsigned int bombs_amount);

        bool                               isGameOver()                const;
        bool                               isWin()                     const;
        unsigned int                       getLength()                 const;
        unsigned int                       getHeight()                 const;
        unsigned int                       getBombsAmount()            const;
        std::vector<std::shared_ptr<Cell>> getCells()                  const;
        size_t                             getCellsSize()              const;
        std::shared_ptr<Cell>              getCell(int index)          const;

        void setGameOver(bool is_game_over);
        void setWin(bool is_win);
        void setLength(unsigned int new_length);
        void setHeight(unsigned int new_height);

        void cellPush(std::shared_ptr<Cell> cell_ptr);

        void render(unsigned int screen_width, unsigned int screen_height) const;
        void input(unsigned int screen_width, unsigned int screen_height);
};
