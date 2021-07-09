#include "game.h"

Game::Game() : grid(0,0,0,0,emptyCell),
               gridTemporary(0,0,0,0,emptyCell),
               emptyCell(EmptyCell(Texture2D{0})) // Did not want to do any of this but compiler forced me to
{
    InitWindow(windowWidth, windowHeight, "malloc(memory);");

    screenTexture = LoadRenderTexture(renderWidth, renderHeight);

    emptyTileTexture = LoadTexture("EmptyTile.png");
    emptyCell = EmptyCell(emptyTileTexture);
    grid = Grid(12, 7, 32, 32, emptyCell);
    gridTemporary = Grid(12, 1, 32, 32, emptyCell);
}

void Game::Update() {
    grid.Update();
    gridTemporary.Update();
}

void Game::Draw() {
    Texture2D gridTexture = grid.Draw();
    Texture2D gridTemporaryTexture = gridTemporary.Draw();

    BeginTextureMode(screenTexture);
        ClearBackground(backgroundColor);
        DrawTexture(gridTexture, 16, 64, WHITE);
        DrawTexture(gridTemporaryTexture, 16, 9.5 * 32, WHITE);
    EndTextureMode();

    BeginDrawing();
        Rectangle textureRec { 0, 0, (float)screenTexture.texture.width, (float)-screenTexture.texture.height };
        Rectangle windowRec { 0, 0, (float)windowWidth, (float)windowHeight };
        Vector2 position { 0, 0 };
        DrawTexturePro(screenTexture.texture, textureRec, windowRec, position, 0, WHITE);
    EndDrawing();
}

void Game::UnloadGame() {
    grid.ResizeGrid(0, 0);
    gridTemporary.ResizeGrid(0, 0);

    UnloadTexture(emptyTileTexture);

    UnloadRenderTexture(screenTexture);
    CloseWindow();        // Close window and OpenGL context
}

void Game::UpdateDrawFrame() {
    Update();
    Draw();
}