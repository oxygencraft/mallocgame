#include <raylib.h>
#include "emptycell.h"
#include "grid.h"


int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    int renderWidth = 512;
    int renderHeight = 336;

    int windowWidth = renderWidth * 2;
    int windowHeight = renderHeight * 2;

    InitWindow(windowWidth, windowHeight, "malloc(memory);");

    RenderTexture2D screenTexture = LoadRenderTexture(renderWidth, renderHeight);
    Color backgroundColor = Color { 42, 23, 59, 255};

    Texture2D emptyTileTexture = LoadTexture("EmptyTile.png");
    EmptyCell emptyCell = EmptyCell(emptyTileTexture);
    Grid grid = Grid(12, 7, 32, 32, emptyCell);
    Grid gridTemporary = Grid(12, 2, 32, 32, emptyCell);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        grid.Update();
        gridTemporary.Update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        Texture2D gridTexture = grid.Draw();
        Texture2D gridTemporaryTexture = gridTemporary.Draw();

        BeginTextureMode(screenTexture);
            ClearBackground(backgroundColor);
            DrawTexture(gridTexture, 16, 16, WHITE);
            DrawTexture(gridTemporaryTexture, 16, 8 * 32, WHITE);
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