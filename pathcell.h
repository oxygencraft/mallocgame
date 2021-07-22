#pragma once

#include "cell.h"

class PathCell : public Cell {
public:
    int gCost;
    int hCost;
    int fCost;
    int movementCost;
    PathCell* previousCell;

    Cell* referenceCell;

    void Update() override;
    Texture2D Draw() override;
    PathCell& Clone() override;
};
