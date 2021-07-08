#ifndef MALLOCGAME_CELL_H
#define MALLOCGAME_CELL_H


#include "object.h"

class Grid;

class Cell : public Object {
    public:
        Vector2 GetGridPosition();
        Grid& GetOwner();
        Cell& Clone() override = 0;
    private:
        Vector2 gridPosition;
        Grid* owner;
        friend class Grid;
};


#endif //MALLOCGAME_CELL_H
