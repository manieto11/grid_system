#include "grid.h"

Vector2Int GetPivot(Vector2Int pos)
{
    return {pos.x & ~(GRID_CHUNK_SIZE - 1), pos.y & ~(GRID_CHUNK_SIZE - 1)};
}

uint_fast8_t GridContainsPivot(const Grid *grid, Vector2Int pivot)
{
    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        if (grid->chunks[i] == nullptr)
            continue;
        if (grid->pivots[i] == pivot)
            return 1;
    }
    return 0;
}

bool operator==(const Vector2Int &a, const Vector2Int &b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector2Int &a, const Vector2Int &b)
{
    return a.x != b.x || a.y != b.y;
}

Grid *InitGrid()
{
    Grid *grid = new Grid();

    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        grid->chunks[i] = nullptr;
    }
    grid->origin = {0, 0};

    return grid;
}

Grid *InitGrid(Vector2Int origin)
{
    Grid *grid = new Grid();

    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        grid->chunks[i] = nullptr;
    }
    grid->origin = origin;

    return grid;
}

void CloseGrid(Grid *grid)
{
    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        if (grid->chunks[i] == nullptr)
            continue;
        MemFree(grid->chunks[i]);
    }
    delete grid;
}

void LoadChunk(Grid *grid, const Vector2Int pos)
{
    if (GridContainsPivot(grid, pos))
    {
        TraceLog(LOG_WARNING, "Grid already has chunk loaded!");
        return;
    }
    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        if (grid->chunks[i] != nullptr)
            continue;
        GridChunk *chunk = static_cast<GridChunk *>(MemAlloc(sizeof(GridChunk)));
        // if (FileExists())
        grid->chunks[i] = chunk;
        grid->pivots[i] = GetPivot(pos);
        TraceLog(LOG_INFO, "Chunk stored in {%d, %d}", grid->pivots[i].x, grid->pivots[i].y);
        return;
    }
    TraceLog(LOG_ERROR, "Grid capacity full, could not load chunk from {%d, %d}!", pos.x, pos.y);
}

void SaveChunk(Grid *grid, const Vector2Int pos)
{

}

void UnloadChunk(Grid *grid, const Vector2Int pos)
{
    Vector2Int pivot = GetPivot(pos);
    for (int i = 0; i < MAX_LOADED_CHUNKS; ++i)
    {
        if (grid->pivots[i] != pivot) continue;
        
        

        TraceLog(LOG_INFO, "Unloaded chunk from {%d, %d}.", pos.x, pos.y);
    }
}
