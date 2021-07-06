#include <raylib.h>
#include "emptycell.h"
#include "grid.h"


int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    int windowWidth = 1024;
    int windowHeight = 768;

    int renderWidth = 256;
    int renderHeight = 192;

    InitWindow(windowWidth, windowHeight, "malloc(memory);");

    RenderTexture2D screenTexture = LoadRenderTexture(renderWidth, renderHeight);

    Texture2D emptyTileTexture = LoadTexture("EmptyTile.png");
    EmptyCell emptyCell = EmptyCell(emptyTileTexture);
    emptyCell.Draw();
    Grid grid = Grid(4, 4, 32, 32, emptyCell);

    RenderTexture2D tileTexture = LoadRenderTexture(32, 32);
    RenderTexture2D tileTexture2 = LoadRenderTexture(32, 32);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        grid.Update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        Texture2D gridTexture = grid.Draw();

        BeginTextureMode(screenTexture);
            ClearBackground(RAYWHITE);
            DrawTexture(gridTexture, 0, 0, WHITE);
        EndTextureMode();

        BeginDrawing();
            Rectangle textureRec { 0, 0, (float)screenTexture.texture.width, (float)-screenTexture.texture.height };
            Rectangle windowRec { 0, 0, (float)windowWidth, (float)windowHeight };
            Vector2 position { 0, 0 };
            DrawTexturePro(screenTexture.texture, textureRec, windowRec, position, 0, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}