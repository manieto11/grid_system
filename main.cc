#include "grid.h"
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "grid-system");
    SetExitKey(KEY_NULL);

    Grid *grid = InitGrid();

    LoadChunk(grid, {0, 0});
    LoadChunk(grid, {65, 0});
    LoadChunk(grid, {213, 0});
    LoadChunk(grid, {0, 120});
    LoadChunk(grid, {0, 3000});
    LoadChunk(grid, {240, 450});
    LoadChunk(grid, {-120, 330});
    LoadChunk(grid, {0, -1000});
    LoadChunk(grid, {990, 990});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseGrid(grid);
}