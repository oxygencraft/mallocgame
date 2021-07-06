#ifndef MALLOCGAME_CELL_H
#define MALLOCGAME_CELL_H


#include "object.h"

class Grid;

class Cell : public Object {
    public:
        int GetGridX();
        int GetGridY();
        Grid& GetOwner();
        Cell& Clone() override = 0;
    private:
        int gridX;
        int gridY;
        Grid* owner;
        friend class Grid;
};


#endif //MALLOCGAME_CELL_H
