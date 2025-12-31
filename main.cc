#include "grid.h"
#include "raylib.h"
#include <cmath>

int main()
{
    InitWindow(800, 600, "grid-system");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Texture texture = LoadTexture("./default_grid_2.png");

    GridChunk grid;

    grid.SetTexture(&texture);

    Camera2D cam = {0};

    cam.offset = {0, static_cast<float>(GetScreenHeight()) - GRID_SPRITE_HEIGHT};
    cam.target = {0, 0};
    cam.zoom = 1.0f;
    cam.rotation = 0.0f;

    grid.SetTile(0, 0, true);
    grid.SetTile(32, 32, true);

    while (!WindowShouldClose())
    {
        bool m1 = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        if (m1 or IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), cam);
            if (mousePos.y < 0) mousePos.y -= GRID_SPRITE_HEIGHT;
            grid.SetTile(static_cast<int>(mousePos.x) / GRID_SPRITE_WIDTH, static_cast<int>(-mousePos.y) / GRID_SPRITE_HEIGHT, m1);
            //TraceLog(LOG_INFO, "Changing tile in {%d, %d}", static_cast<int>(mousePos.x) / GRID_SPRITE_WIDTH, static_cast<int>(-mousePos.y) / GRID_SPRITE_HEIGHT);
        }

        if (IsKeyDown(KEY_UP))
            cam.offset.y++;
        if (IsKeyDown(KEY_DOWN))
            cam.offset.y--;

        BeginDrawing();
        ClearBackground(DARKBLUE);
        BeginMode2D(cam);
        grid.Draw();
        EndMode2D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();
}