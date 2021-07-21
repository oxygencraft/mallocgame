#pragma once

#include <memory>
#include <vector>
#include <raylib.h>
#include "cell.h"

class Grid : public Object {
public:
    Grid(int posX, int posY, int cellNumX, int cellNumY, int cellSizeX, int cellSizeY, Cell& emptyCell, bool noDrawing = false);
    Cell& GetCell(int x, int y);
    Cell& GetCellFromScreenPosition(int x, int y);
    void SetCell(int x, int y, Cell& cell);
    void SetEmptyCell(int x, int y);
    void ResizeGrid(int cellNumX, int cellNumY);
    Texture2D Draw() override;
    void Update() override;
    Grid& Clone() override;
    int GetCellNumX();
    int GetCellNumY();
    int GetCellSizeX();
    int GetCellSizeY();
private:
    int cellNumX;
    int cellNumY;
    int cellSizeX;
    int cellSizeY;
    Cell* emptyCell;
    std::vector<std::vector<Cell*>> cells;
    std::vector<std::vector<RenderTexture2D>> cellTextures;
    RenderTexture2D gridTexture;
    bool noDrawing;
    Cell& GetEmptyCell(int x, int y);
};
