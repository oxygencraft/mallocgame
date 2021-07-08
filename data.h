#ifndef MALLOCGAME_DATA_H
#define MALLOCGAME_DATA_H

#include <raylib.h>

#include "datacell.h"


struct Data {
    int importance;
    DataCell cells[];
};



#endif //MALLOCGAME_DATA_H
