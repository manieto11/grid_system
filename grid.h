#ifndef GRID_H
#define GRID_H

#define CHUNK_SIZE 64
#define GRID_SPRITE_WIDTH 32
#define GRID_SPRITE_HEIGHT 32

#include "raylib.h"

class GridChunk
{
private:
    bool tiles[CHUNK_SIZE][CHUNK_SIZE];
    unsigned char tile_sprites[CHUNK_SIZE][CHUNK_SIZE];
    const Texture* texture;

    void AddTile(int x, int y);
    void UpdateTile(int x, int y);
    void RemoveTile(int x, int y);

public:
    GridChunk();

    void Draw();
    bool GetTile(int x, int y);
    void SetTile(int x, int y, bool tile);
    void SetTexture(const Texture* texture);
};

#endif