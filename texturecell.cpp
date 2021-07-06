#include "texturecell.h"

Texture2D TextureCell::Draw() {
    return GetTexture();
}

Texture2D TextureCell::GetTexture() {
    return texture;
}

void TextureCell::SetTexture(Texture2D texture) {
    this->texture = texture;
}

TextureCell::TextureCell(Texture2D texture) {
    SetTexture(texture);
}
