#ifndef MALLOCGAME_GRID_H
#define MALLOCGAME_GRID_H

#include <memory>
#include <vector>
#include <raylib.h>
#include "cell.h"

class Grid : public Object {
    public:
        Grid(int cellNumX, int cellNumY, int cellSizeX, int cellSizeY, Cell& emptyCell);
        Cell& GetCell(int x, int y);
        void SetCell(int x, int y, Cell& cell);
        void MoveCell(Cell& origin, Cell& target, bool destroyTarget = false);
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
        Cell& emptyCell;
        std::vector<std::vector<Cell*>> cells;
        std::vector<std::vector<RenderTexture2D>> cellTextures;
        RenderTexture2D gridTexture;
};


#endif //MALLOCGAME_GRID_H
