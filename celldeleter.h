#pragma once

#include <vector>
#include "grid.h"
#include "util.h"

class CellDeleter : public Object {
public:
    void Update() override;
    Texture2D Draw() override;
    Object& Clone() override;
    CellDeleter(std::vector<Grid*> grids, Vector2 position, Texture2D buttonTexture, Texture2D buttonEnabledTexture);
private:
    std::vector<Grid*> grids;
    bool isDeleting = false;
    Texture2D texture;
    Texture2D enabledTexture;
};



