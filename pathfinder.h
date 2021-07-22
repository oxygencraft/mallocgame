#pragma once

#include "grid.h"
#include "pathcell.h"
#include <stack>
#include <unordered_set>

class Pathfinder {
public:
    std::stack<PathCell> FindPath(int startX, int startY, int endX, int endY);
    bool HasGridChanged();
    Pathfinder(Grid& grid);
private:
    Grid* referenceGrid;
    Grid pathfinderGrid;
    std::stack<PathCell> CalculatePath(PathCell endCell);
    PathCell* GetLowestFCostCell(std::unordered_set<PathCell*>& openCells);
    std::unordered_set<PathCell*> GetNeighbours(PathCell& pathCell);
    int CalculateDistanceCost(PathCell& cellA, PathCell& cellB);
    PathCell& GetPathCell(int x, int y);
};
