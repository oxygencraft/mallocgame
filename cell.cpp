#include "cell.h"

Vector2 Cell::GetGridPosition() {
    return gridPosition;
}

Grid& Cell::GetOwner() {
    return *owner;
}