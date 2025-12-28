#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include <stdint.h>

#define GRID_CHUNK_SIZE 64
#define GRID_PIXEL_SIZE 32
#define MAX_LOADED_CHUNKS 8

#ifndef DEC_VECTOR2INT_TYPE
#define DEC_VECTOR2INT_TYPE

struct Vector2Int
{
    int x, y;
};

bool operator==(const Vector2Int& a, const Vector2Int& b);
bool operator!=(const Vector2Int& a, const Vector2Int& b);

#endif

typedef uint_fast64_t GridChunk[GRID_CHUNK_SIZE];

struct Grid
{
    Vector2Int origin;
    GridChunk* chunks[MAX_LOADED_CHUNKS];
    Vector2Int pivots[MAX_LOADED_CHUNKS];
};

// Creates a new empty grid.
Grid *InitGrid();

// Creates a new empty grid centered in the origen.
Grid *InitGrid(Vector2Int origen);

// Deletes a grid.
void CloseGrid(Grid *grid);

// Loads chunk that contains the position <pos>.
void LoadChunk(Grid *grid, const Vector2Int pos);

// Stores the chunk information in storage.
void SaveChunk(Grid *grid, const Vector2Int pos);

// Unloads chunk that contains the position <pos>.
void UnloadChunk(Grid *grid, const Vector2Int pos);

// Draws the grid.
void DrawGrid(const Grid *grid);

#endif