#include "pathcell.h"

void PathCell::Update() {
    // I don't know what this should do
    // Probably nothing so I'll just leave this an empty function
}

Texture2D PathCell::Draw() {
    // I guess this can just be a debug view of g cost, h cost and f cost and the open/close state?
    // Anyway, I don't feel like implementing that right now so I'm just going to return a blank texture

    static Image image = GenImageColor(32, 32, Color { 0, 0, 0, 0,});
    static Texture2D texture = LoadTextureFromImage(image);

    return texture;
}

PathCell& PathCell::Clone() {
    return *(new PathCell(*this));
}
