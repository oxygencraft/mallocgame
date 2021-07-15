#include "movingcell.h"

Texture2D MovingCell::Draw() {
    return GetTexture();
}

void MovingCell::Update() {

}

MovingCell& MovingCell::Clone() {
    const Texture2D texture = GetTexture();
    return *(new MovingCell(texture));
}
