#pragma once

#include <raylib.h>
#include "datacell.h"

struct Data {
    int importance;
    std::vector<DataCell> cells;
};
