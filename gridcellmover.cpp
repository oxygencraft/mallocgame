#include "gridcellmover.h"
#include "datacell.h"
#include "emptycell.h"
#include "game.h"

void GridCellMover::Update() {
    // When we are not moving any cells

    // If necessary, convert mouse position upscaled position (window size) to normal position (render size)
    int mousePositionX = GetMouseX() / 2;
    int mousePositionY = GetMouseY() / 2;

    // Check if left mouse button is being pressed
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && cells.empty()) {
        // If so, check if it is in the position of a grid in the list of grids
        Grid* grid = GetGridFromPosition(mousePositionX, mousePositionY);
        if (grid != nullptr) {
            // If it is, where in the grid is it and what cell is the mouse on
            Cell& cell = grid->GetCellFromScreenPosition(mousePositionX - grid->position.x,
                                                         mousePositionY - grid->position.y);
            DataCell* dataCell = dynamic_cast<DataCell*>(&cell);
            if (dataCell) { // Is it on a data cell
                // Store the grid and cell positions to revert back to later
                originalGrid = grid;
                originalPositionX = dataCell->GetGridPosition().x;
                originalPositionY = dataCell->GetGridPosition().y;
                // Store mouse offset relative to cell
                mouseOffsetX = mousePositionX - dataCell->position.x;
                mouseOffsetY = mousePositionY - dataCell->position.y;

                // Check adjacent cells and check if they should be moved
                int currentDataIndex = dataCell->GetIndex();
                for (int i = originalPositionX; i < grid->GetCellNumX(); ++i) {
                    DataCell* currentDataCell = dynamic_cast<DataCell*>(&grid->GetCell(i, originalPositionY));
                    if (!currentDataCell)
                        break;
                    Data& data = currentDataCell->GetDataOwner();
                    if (currentDataCell->GetIndex() != currentDataIndex || &data != &dataCell->GetDataOwner())
                        break;
                    ++currentDataIndex;

                    // Copy those cells to this class and in the grid, set those cells to empty cells
                    cells.push_back(&currentDataCell->Clone());
                    grid->SetEmptyCell(i, originalPositionY);
                }
            }
        }
    }

    if (!cells.empty()) {
        // Check if left mouse button is still being pressed

        // If so, continue to update the position and draw those cells
        // Handled in Draw function

        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { // If not, find the grid position and cells that the mouse position is in
            Grid* grid = GetGridFromPosition(mousePositionX, mousePositionY);
            if (grid != nullptr) {
                Cell& cell = grid->GetCellFromScreenPosition(mousePositionX - grid->position.x, mousePositionY - grid->position.y);
                int x = cell.GetGridPosition().x;
                int y = cell.GetGridPosition().y;
                bool validPosition = true;

                // Check if all cells are in a valid position in the grid
                for (int i = 0; i < cells.size(); ++i) {
                    if (x + i > grid->GetCellNumX()) {
                        validPosition = false;
                        break;
                    }

                    Cell* checkCell = &grid->GetCell(x + i, y);
                    EmptyCell* emptyCell = dynamic_cast<EmptyCell*>(checkCell);
                    if (!emptyCell) {
                        validPosition = false;
                        break;
                    }
                }

                if (validPosition) {  // If it was successful, set the cells in the grid to the cells we are moving.
                    for (int i = 0; i < cells.size(); ++i) {
                        grid->SetCell(x + i, y, cells[i]->Clone());
                    }
                    cells.clear();
                    return;
                }
            }

            // If it was not successful (mouse not in grid or last cell out of grid), revert the cells back to where they were
            for (int i = 0; i < cells.size(); ++i) {
                originalGrid->SetCell(originalPositionX + i, originalPositionY, cells[i]->Clone());
            }
            cells.clear();
        }
    }
}

Texture2D GridCellMover::Draw() {
    int mousePositionX = GetMouseX() / 2;
    int mousePositionY = GetMouseY() / 2;

    if (!renderTextureInitialized) {
        renderTexture = LoadRenderTexture(renderWidth, renderHeight);
        renderTextureInitialized = true;
    }

    // When currently moving cells with left mouse button pressed down
    // Update the position of the cells relative to the mouse position and draw those cells
    BeginTextureMode(renderTexture);
    ClearBackground(Color { 0 , 0, 0, 0 });
    for (int i = 0; i < cells.size(); ++i) {
        DrawTexture(cells[i]->Draw(), mousePositionX - mouseOffsetX + i * 32, mousePositionY - mouseOffsetY, WHITE);
    }
    EndTextureMode();

    return renderTexture.texture;
}


Grid* GridCellMover::GetGridFromPosition(int x, int y) {
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

void GridCellMover::Unload() {
    UnloadRenderTexture(renderTexture);
}


GridCellMover::GridCellMover(std::vector<Grid*> grids) : grids(grids) {

}