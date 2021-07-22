#include "pathfinder.h"
#include "datacell.h"
#include <unordered_set>

std::stack<PathCell> Pathfinder::FindPath(int startX, int startY, int endX, int endY) {
    std::unordered_set<PathCell*> openCells;
    std::unordered_set<PathCell*> closedCells;
    PathCell& startCell = GetPathCell(startX, startY);
    PathCell& endCell = GetPathCell(endX, endY);
    startCell.fCost = 0;
    openCells.insert(&startCell);

    while (openCells.size() > 0) {
        PathCell* currentCell = GetLowestFCostCell(openCells);
        openCells.erase(currentCell);
        closedCells.insert(currentCell);

        if (currentCell == &endCell)
            break;

        for (auto& neighbour : GetNeighbours(*currentCell)) {
            if (closedCells.count(neighbour) > 0)
                continue;

            int newGCost = currentCell->gCost + neighbour->movementCost;
            bool notInOpen = openCells.count(neighbour) == 0;

            if (newGCost < neighbour->gCost || notInOpen) {
                neighbour->gCost = newGCost;
                neighbour->hCost = CalculateDistanceCost(*neighbour, endCell);
                neighbour->fCost = neighbour->gCost + neighbour->hCost;
                neighbour->previousCell = currentCell;

                if (notInOpen)
                    openCells.insert(neighbour);
            }
        }
    }

    return CalculatePath(endCell);
}

std::stack<PathCell> Pathfinder::CalculatePath(PathCell endCell) {
    std::stack<PathCell> path;

    PathCell currentCell = endCell;

    while (currentCell.previousCell != nullptr) {
        path.push(currentCell);
        currentCell = *currentCell.previousCell;
    }

    return path;
}

PathCell* Pathfinder::GetLowestFCostCell(std::unordered_set<PathCell*> &openCells) {
    PathCell* lowestCell;
    int lowestCost = 999999;

    for (auto& cell : openCells) {
        if (cell->fCost < lowestCost) {
            lowestCell = cell;
            lowestCost = cell->fCost;
        }
    }

    return lowestCell;
}

std::unordered_set<PathCell*> Pathfinder::GetNeighbours(PathCell& pathCell) {
    std::unordered_set<PathCell*> neighbours;
    int x = pathCell.position.x;
    int y = pathCell.position.y;

    // Left
    if (x - 1 >= 0) neighbours.insert(&GetPathCell(x - 1, y));
    // Right
    if (x + 1 < pathfinderGrid.GetCellNumX()) neighbours.insert(&GetPathCell(x + 1, y));
    // Up
    if (y + 1 < pathfinderGrid.GetCellNumY()) neighbours.insert(&GetPathCell(x, y + 1));
    // Down
    if (y - 1 >= 0) neighbours.insert(&GetPathCell(x, y - 1));
}

int Pathfinder::CalculateDistanceCost(PathCell& startCell, PathCell& endCell) {
    return abs(startCell.position.x - endCell.position.x) + abs(startCell.position.y - endCell.position.y);
}

bool Pathfinder::HasGridChanged() {
    bool hasChanged = false;

    // This will probably never happen but might as well handle it anyway
    if (pathfinderGrid.GetCellNumX() != referenceGrid->GetCellNumX() ||
        pathfinderGrid.GetCellNumY() != referenceGrid->GetCellNumY()) {
        hasChanged = true;
        pathfinderGrid.ResizeGrid(referenceGrid->GetCellNumX(), referenceGrid->GetCellNumY());
    }

    for (int x = 0; x < pathfinderGrid.GetCellNumX(); ++x) {
        for (int y = 0; y < pathfinderGrid.GetCellNumY(); ++y) {
            PathCell& cell = GetPathCell(x, y);

            Cell* referenceCell = &referenceGrid->GetCell(x, y);
            if (cell.referenceCell != referenceCell) {
                hasChanged = true;
                cell.referenceCell = referenceCell;
                if (dynamic_cast<DataCell*>(referenceCell))
                    cell.movementCost = 20;
                else
                    cell.movementCost = 10;
            }
        }
    }

    return hasChanged;
}

Pathfinder::Pathfinder(Grid& grid) : pathfinderGrid(grid) {
    referenceGrid = &grid;

    Vector2 gridPosition = referenceGrid->position;
    int numX = referenceGrid->GetCellNumX();
    int numY = referenceGrid->GetCellNumY();
    int sizeX = referenceGrid->GetCellSizeX();
    int sizeY = referenceGrid->GetCellSizeY();

    PathCell* pathCell = new PathCell();
    pathCell->referenceCell = nullptr;
    pathCell->previousCell = nullptr;
    pathfinderGrid = Grid(gridPosition.x, gridPosition.y, numX, numY, sizeX, sizeY, *pathCell, true);

    HasGridChanged();
}

PathCell& Pathfinder::GetPathCell(int x, int y) {
    return dynamic_cast<PathCell&>(pathfinderGrid.GetCell(x, y));
}
