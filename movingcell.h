#pragma once

#include "texturecell.h"

class MovingCell : public TextureCell {
public:
    Texture2D Draw() override;
    void Update() override;
    MovingCell& Clone() override;
    using TextureCell::TextureCell;
};
