#ifndef MALLOCGAME_GAME_H
#define MALLOCGAME_GAME_H

#include <raylib.h>
#include "grid.h"
#include "emptycell.h"
#include "databuffermanager.h"

static const int renderWidth = 512;
static const int renderHeight = 352;

static const int windowWidth = renderWidth * 2;
static const int windowHeight = renderHeight * 2;

static const Color backgroundColor = Color { 42, 23, 59, 255};

class Game {
    public:
        Game();
        void Update();
        void Draw();
        void UnloadGame();
        void UpdateDrawFrame();

    private:
        RenderTexture2D screenTexture;
        Texture2D emptyTileTexture;
        Texture2D blueTileTexture;
        Texture2D yellowTileTexture;
        Texture2D redTileTexture;
        EmptyCell emptyCell;
        Grid grid;
        Grid bufferGrid;
        DataBufferManager dataManager;
};


#endif //MALLOCGAME_GAME_H
