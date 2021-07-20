#pragma once

#include <raylib.h>
#include "grid.h"
#include "data.h"

void DrawRenderTexture(RenderTexture2D texture, int posX, int posY, Color tint);
void DrawRenderTexture(Texture2D texture, int posX, int posY, Color tint);
Grid* GetGridFromPosition(int x, int y, std::vector<Grid*> grids);
int GetDataCellListIndex(int dataCellIndex, Data& data);
