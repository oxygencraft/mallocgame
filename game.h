#pragma once

#include <raylib.h>
#include "grid.h"
#include "emptycell.h"
#include "databuffermanager.h"
#include "gridcellmover.h"
#include "movingcell.h"
#include "dataallocationmanager.h"
#include "celldeleter.h"

static const int renderWidth = 512;
static const int renderHeight = 352;

static const int windowWidth = renderWidth * 2;
static const int windowHeight = renderHeight * 2;

static const Color backgroundColor = Color { 42, 23, 59, 255};
static const Color textColor = Color { 76, 92, 135, 255};

class Game {
public:
    Game();
    void Update();
    void Draw();
    void UnloadGame();
    void UpdateDrawFrame();

private:
    RenderTexture2D screenTexture;
    Texture2D logoTexture;
    Texture2D emptyTileTexture;
    Texture2D blueTileTexture;
    Texture2D yellowTileTexture;
    Texture2D redTileTexture;
    Texture2D robotTexture;
    Texture2D deleteButtonTexture;
    Texture2D deleteEnabledButtonTexture;
    EmptyCell emptyCell;
    MovingCell movingCell;
    Grid grid;
    Grid bufferGrid;
    DataAllocationManager dataAllocationManager;
    DataBufferManager dataBufferManager;
    GridCellMover gridCellMover;
    CellDeleter cellDeleter;
};
