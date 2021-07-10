#ifndef MALLOCGAME_GRIDCELLMOVER_H
#define MALLOCGAME_GRIDCELLMOVER_H


#include <vector>
#include "grid.h"

class GridCellMover {
    public:
        void Update();
        GridCellMover(std::vector<Grid> grids);
    private:
        std::vector<Grid> grids;
};


#endif //MALLOCGAME_GRIDCELLMOVER_H
