#pragma once

#include "object.h"

class Grid;
class GridCellMover;

class Cell : public Object {
public:
    Vector2 GetGridPosition();
    Grid* GetOwner();
    Cell& Clone() override = 0;
private:
    Vector2 gridPosition;
    Grid* owner;
    friend class Grid;
    friend class GridCellMover;
};
