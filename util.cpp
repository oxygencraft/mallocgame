#include "util.h"

void DrawRenderTexture(RenderTexture2D texture, int posX, int posY, Color tint) {
    DrawRenderTexture(texture.texture, posX, posY, tint);
}

void DrawRenderTexture(Texture2D texture, int posX, int posY, Color tint) {
    Rectangle rectangle { 0, 0, (float)texture.width, (float)-texture.height };
    Vector2 pos = Vector2 { (float)posX, (float)posY };
    DrawTextureRec(texture, rectangle, pos, tint);
}

Grid* GetGridFromPosition(int x, int y, std::vector<Grid*> grids) {
    for (auto& grid : grids) {
        int startPosX = grid->position.x;
        int startPosY = grid->position.y;
        int gridSizeX = grid->GetCellNumX() * grid->GetCellSizeX() + startPosX;
        int gridSizeY = grid->GetCellNumY() * grid->GetCellSizeY() + startPosY;

        if (startPosX < x && gridSizeX > x && startPosY < y && gridSizeY > y) {
            return grid;
        }
    }

    return nullptr;
}

int GetDataCellListIndex(int dataCellIndex, Data& data) {
    for (int i = 0; i < data.cells.size(); ++i) {
        if (data.cells[i] && data.cells[i]->GetIndex() == dataCellIndex)
            return i;
    }
}