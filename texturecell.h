#pragma once

#include <raylib.h>
#include "cell.h"

class TextureCell : public Cell {
public:
    TextureCell(Texture2D texture);
    Texture2D GetTexture();
    Texture2D Draw() override;
protected:
    void SetTexture(Texture2D texture);
private:
    Texture2D texture;
};
