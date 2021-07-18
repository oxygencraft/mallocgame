#pragma once

#include <raylib.h>

class Object {
public:
    Vector2 position;
    virtual void Update() = 0;
    virtual Texture2D Draw() = 0;
    virtual Object& Clone() = 0;
    virtual ~Object() = default;
};
