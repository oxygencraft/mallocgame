#ifndef MALLOCGAME_MOVINGCELL_H
#define MALLOCGAME_MOVINGCELL_H


#include "texturecell.h"

class MovingCell : public TextureCell {
    Texture2D Draw() override;
    void Update() override;
    MovingCell& Clone() override;
    using TextureCell::TextureCell;
};


#endif //MALLOCGAME_MOVINGCELL_H
