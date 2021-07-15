#include "util.h"

void DrawRenderTexture(RenderTexture2D texture, int posX, int posY, Color tint) {
    DrawRenderTexture(texture.texture, posX, posY, tint);
}

void DrawRenderTexture(Texture2D texture, int posX, int posY, Color tint) {
    Rectangle rectangle { 0, 0, (float)texture.width, (float)-texture.height };
    Vector2 pos = Vector2 { (float)posX, (float)posY };
    DrawTextureRec(texture, rectangle, pos, tint);
}