#ifndef MALLOCGAME_OBJECT_H
#define MALLOCGAME_OBJECT_H

#include <raylib.h>

class Object {
    public:
        int x;
        int y;
        virtual void Update() = 0;
        virtual Texture2D Draw() = 0;
        virtual Object& Clone() = 0;
};


#endif //MALLOCGAME_OBJECT_H
