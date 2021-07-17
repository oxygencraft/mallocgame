#include "game.h"
#include "util.h"

Game::Game() : grid(0,0,0,0,0,0,emptyCell),
               bufferGrid(0,0,0, 0, 0, 0, emptyCell),
               emptyCell(EmptyCell(Texture2D{0})),
               movingCell(MovingCell(Texture2D{0})),
               dataManager(0,grid,blueTileTexture,yellowTileTexture,redTileTexture),
               gridCellMover(std::vector<Grid*>(), movingCell)
               // Did not want to do any of this but compiler forced me to
               // Also prevents me from making members references in these objects so I have to use pointers
{
    InitWindow(windowWidth, windowHeight, "malloc(memory);");

    screenTexture = LoadRenderTexture(renderWidth, renderHeight);

    logoTexture = LoadTexture("resources/Logo.png");
    emptyTileTexture = LoadTexture("resources/EmptyTile.png");
    blueTileTexture = LoadTexture("resources/BlueTile.png");
    yellowTileTexture = LoadTexture("resources/YellowTile.png");
    redTileTexture = LoadTexture("resources/RedTile.png");

    emptyCell = EmptyCell(emptyTileTexture);
    movingCell = MovingCell(emptyTileTexture);
    grid = Grid(16, 64, 12, 7, 32, 32, emptyCell);
    bufferGrid = Grid(16, 9.5 * 32, 12, 1, 32, 32, emptyCell);
    dataManager = DataBufferManager(8, bufferGrid, blueTileTexture, yellowTileTexture, redTileTexture);
    gridCellMover = GridCellMover(std::vector<Grid*> { &grid, &bufferGrid}, movingCell);
}

void Game::Update() {
    grid.Update();
    bufferGrid.Update();
    dataManager.Update();
    gridCellMover.Update();
}

void Game::Draw() {
    Texture2D gridTexture = grid.Draw();
    Texture2D bufferGridTexture = bufferGrid.Draw();
    Texture2D gridMoverTexture = gridCellMover.Draw();

    BeginTextureMode(screenTexture);
        ClearBackground(backgroundColor);

        DrawRenderTexture(gridTexture, 16, 64, WHITE);
        DrawRenderTexture(bufferGridTexture, 16, 9.5 * 32, WHITE);

        DrawTexture(logoTexture, 16, 0, WHITE);
        DrawText("This game is heavily unfinished and currently unplayable, see itch.io page for more details.", 16, 52, 5, textColor);

        DrawRenderTexture(gridMoverTexture, 0, 0, WHITE);
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
    bufferGrid.ResizeGrid(0, 0);
    gridCellMover.Unload();

    UnloadTexture(logoTexture);
    UnloadTexture(emptyTileTexture);
    UnloadTexture(blueTileTexture);
    UnloadTexture(yellowTileTexture);
    UnloadTexture(redTileTexture);

    UnloadRenderTexture(screenTexture);
    CloseWindow();        // Close window and OpenGL context
}

void Game::UpdateDrawFrame() {
    Update();
    Draw();
}