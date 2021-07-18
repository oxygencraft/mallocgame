#pragma once

#include <raylib.h>
#include "texturecell.h"

class EmptyCell : public TextureCell {
public:
    Texture2D Draw() override;
    void Update() override;
    EmptyCell& Clone() override;
    using TextureCell::TextureCell;
};
