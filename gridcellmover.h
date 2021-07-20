#pragma once

#include <vector>
#include "grid.h"
#include "util.h"

class GridCellMover {
public:
    void Update();
    Texture2D Draw();
    void Unload();
    GridCellMover(std::vector<Grid*> grids, Cell& movingCell);
private:
    std::vector<Grid*> grids;
    std::vector<Cell*> cells;
    Cell* movingCell;
    Grid* originalGrid;
    int originalPositionX;
    int originalPositionY;
    int mouseOffsetX;
    int mouseOffsetY;
    RenderTexture2D renderTexture;
    bool renderTextureInitialized = false;
};
