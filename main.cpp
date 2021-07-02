#include <raylib.h>

void Update() {

}

void Draw() {
    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 25, 80, 5, LIGHTGRAY);
}

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int windowWidth = 1024;
    int windowHeight = 768;

    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "malloc(memory);");

    int renderWidth = 256;
    int renderHeight = 192;
    RenderTexture2D screenTexture = LoadRenderTexture(renderWidth, renderHeight);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginTextureMode(screenTexture);
            Draw();
        EndTextureMode();

        //windowWidth = GetScreenWidth();
        //windowHeight = GetScreenHeight();

        BeginDrawing();
            Rectangle textureRec;
            textureRec.x = 0;
            textureRec.y = 0;
            textureRec.width = (float)screenTexture.texture.width;
            textureRec.height = (float)-screenTexture.texture.height;
            Rectangle windowRec;
            windowRec.x = 0;
            windowRec.y = 0;
            windowRec.width = (float)windowWidth;
            windowRec.height = (float)windowHeight;
            Vector2 position;
            position.x = 0;
            position.y = 0;
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