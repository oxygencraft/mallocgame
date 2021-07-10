#include "gridcellmover.h"

void GridCellMover::Update() {
    // When we are not moving any cells


    // Check if left mouse button is being pressed
    // If necessary, convert mouse position upscaled position (window size) to normal position (render size)

    // If so, check if it is in the position of a grid in the list of grids
    // If it is, where in the grid is it and what cell is the mouse on

    // Store the grid and cell positions to revert back to later
    // Copy those cells to this class and in the grid, set those cells to empty cells
    // Update the position of the cells relative to the mouse position and draw those cells



    // When currently moving cells with left mouse button pressed down


    // Check if left mouse button is still being pressed

    // If so, continue to update the position and draw those cells

    // If not, find the grid position and cells that the mouse position is in

    // If it was successful, set the cells in the grid to the cells we are moving.
    // If it was not successful (mouse not in grid), revert the cells back to where they were
}

GridCellMover::GridCellMover(std::vector<Grid> grids) {

}
