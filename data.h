#pragma once

#include <raylib.h>
#include "datacell.h"
#include <vector>

struct Data {
    int importance;
    std::vector<DataCell*> cells;
};
