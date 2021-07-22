#include "grid.h"
#include "util.h"

Grid::Grid(int posX, int posY, int cellNumX, int cellNumY, int cellSizeX, int cellSizeY, Cell& emptyCell, bool noDrawing) {
    this->cellNumX = 0;  // Set these to 0 so ResizeGrid() works properly
    this->cellNumY = 0;
    this->position = Vector2 { (float)posX, (float)posY };
    this->cellSizeX = cellSizeX;
    this->cellSizeY = cellSizeY;
    this->emptyCell = &emptyCell.Clone();
    this->noDrawing = noDrawing;

    if (cellNumX <= 0 || cellNumY <= 0)
        return;

    ResizeGrid(cellNumX, cellNumY);
}

Cell& Grid::GetCell(int x, int y) {
    return *(cells[x][y]);
}

void Grid::SetCell(int x, int y, Cell& cell) {
    cell.gridPosition = Vector2 { (float)x, (float)y };
    cell.position = Vector2 { (float)(x * cellSizeX) + position.x, (float)(y * cellSizeY) + position.y };
    cell.owner = this;
    cells[x][y] = &cell;
}

Cell& Grid::GetEmptyCell(int x, int y) {
    Cell& emptyCellNew = emptyCell->Clone();
    emptyCellNew.gridPosition = Vector2 { (float)x, (float)y };
    emptyCellNew.position = Vector2 { (float)(x * cellSizeX) + position.x, (float)(y * cellSizeY) + position.y };
    emptyCellNew.owner = this;
    return emptyCellNew;
}

void Grid::SetEmptyCell(int x, int y) {
    cells[x][y] = &GetEmptyCell(x, y);
}

Cell& Grid::GetCellFromScreenPosition(int x, int y) {
    return GetCell(x / GetCellSizeX(), y / GetCellSizeY());
}

void Grid::ResizeGrid(int cellNumX, int cellNumY) {
    int oldX = GetCellNumX();
    int oldY = GetCellNumY();
    this->cellNumX = cellNumX;
    this->cellNumY = cellNumY;

    if (!noDrawing) {
        for (int x = 0; x < cellTextures.size(); ++x) { // For every column that currently exists,
            if (cellNumY > oldY) { // Add textures if we need more rows
                for (int i = 0; i < cellNumY - oldY; ++i) {
                    cellTextures[x].push_back(RenderTexture2D { 0 });
                }
            } else if (cellNumY < oldY) { // Unload and remove textures if we need less rows
                for (int i = oldY - 1; i > oldY - cellNumY; --i) {
                    UnloadRenderTexture(cellTextures[x][i]);
                    cellTextures[x].pop_back();
                }
            } else {
                break; // If we don't need to change the amount of rows we have
            }
        }

        if (cellNumX > oldX) { // Add columns
            std::vector<RenderTexture2D> yTextureCells;
            yTextureCells.resize(cellNumY, RenderTexture2D { 0 });
            cellTextures.resize(cellNumX, yTextureCells);
        } else if (cellNumX < oldX) { // Remove columns but first unload every texture
            for (int i = oldX - 1; i > oldX - cellNumX; --i) {
                for (int j = 0; j < cellNumY; ++j) {
                    UnloadRenderTexture(cellTextures[i][j]);
                }
                cellTextures.pop_back();
            }
        }
    }

    gridTexture = LoadRenderTexture(GetCellNumX() * GetCellSizeX(), GetCellNumY() * GetCellSizeY());

    for (int y = 0; y < cells.size(); ++y) { // For every column that currently exists,
        if (cellNumY > oldY) { // Add empty cells if we need more rows
            for (int i = 0; i < cellNumY - oldY; ++i) {
                cells[y].push_back(&GetEmptyCell(y, i));
            }
        } else if (cellNumY < oldY) { // Delete and remove cells if we need less rows
            for (int i = oldY - 1; i > oldY - cellNumY; --i) {
                delete cells[y][i];
                cells[y].pop_back();
            }
        } else {
            break; // If we don't need to change the amount of rows we have
        }
    }

    if (cellNumX > oldX) {
        for (int i = 0; i < cellNumX - oldX; ++i) { // Add columns with empty cells if we need more columns
            std::vector<Cell*> cellsY;
            for (int y = 0; y < cellNumY; ++y) {
                cellsY.push_back(&GetEmptyCell(i, y));
            }
            cells.push_back(cellsY);
        }
    } else if (cellNumX < oldX) { // Delete every cell in column and then delete this column
        for (int i = oldX - 1; i > oldX - cellNumX; --i) {
            for (int j = 0; j < cellNumY; ++j) {
                delete cells[i][j];
            }
            cells.pop_back();
        }
    }
}

Texture2D Grid::Draw() {
    if (noDrawing)
        return gridTexture.texture;

    for (int x = 0; x < GetCellNumX(); ++x) {
        for (int y = 0; y < GetCellNumY(); ++y) {
            if (cellTextures[x][y].id == 0)
                cellTextures[x][y] = LoadRenderTexture(GetCellSizeX(), GetCellSizeY());
            RenderTexture2D cellRenderTexture = cellTextures[x][y];
            Texture2D cellTexture = cells[x][y]->Draw();

            BeginTextureMode(cellRenderTexture);
                DrawTexture(cellTexture, 0, 0, WHITE);
            EndTextureMode();

            cellTextures[x][y] = cellRenderTexture;
        }
    }

    RenderTexture2D renderTexture = gridTexture;
    BeginTextureMode(renderTexture);
        for (int x = 0; x < GetCellNumX(); ++x) {
            for (int y = 0; y < GetCellNumY(); ++y) {
                DrawRenderTexture(cellTextures[x][y].texture, x * GetCellSizeX(), y * GetCellSizeY(), WHITE);
            }
        }
    EndTextureMode();
    gridTexture = renderTexture;

    return gridTexture.texture;
}

void Grid::Update() {
    for (int x = 0; x < GetCellNumX(); ++x) {
        for (int y = 0; y < GetCellNumY(); ++y) {
            cells[x][y]->Update();
        }
    }
}

Grid& Grid::Clone() {
    return *(new Grid(*this));
}

int Grid::GetCellNumX() { return cellNumX; }
int Grid::GetCellNumY() { return cellNumY; }
int Grid::GetCellSizeX() { return cellSizeX; }
int Grid::GetCellSizeY() { return cellSizeY; }