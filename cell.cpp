#include "cell.h"

int Cell::GetGridX() {
    return gridX;
}

int Cell::GetGridY() {
    return gridY;
}

Grid& Cell::GetOwner() {
    return *owner;
}