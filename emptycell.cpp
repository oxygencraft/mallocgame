#include "emptycell.h"

Texture2D EmptyCell::Draw() {
    // TODO: Add instability texture
    //if (instability && lastInstability != instability) {
    //    Color randomColor = someHowGetRandomColorFromPalette();
    //    DrawPixel(GetRandomValue(0, this->GetTexture().width),
    //              GetRandomValue(0, this->GetTexture().height), randomColor);
    //}

    return GetTexture();
}

void EmptyCell::Update() {

}

EmptyCell& EmptyCell::Clone() {
    const Texture2D texture = GetTexture();
    return *(new EmptyCell(texture));
}
