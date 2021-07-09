#include <raylib.h>
#include "emptycell.h"
#include "grid.h"
#include "game.h"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    Game game;

    //--------------------------------------------------------------------------------------

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    game.UnloadGame();
    //--------------------------------------------------------------------------------------

    return 0;
}