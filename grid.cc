#include "grid.h"

// X, Y
// UP, UP-RIGHT, RIGHT, DOWN-RIGHT, DOWN, DOWN-LEFT, LEFT, UP-LEFT
int grid_directions[2][8] = {{0, 1, 1, 1, 0, -1, -1, -1}, {1, 1, 0, -1, -1, -1, 0, 1}};

unsigned char grid_sprite_offsets_x[256] = {
    0, 7, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, // 0-15
    7, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 1, 0, 1, // 16-31
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 32-47
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 48-63
    6, 6, 0, 0, 1, 5, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, // 64-79
    5, 7, 0, 0, 2, 5, 0, 1, 0, 0, 0, 0, 3, 3, 0, 1, // 80-95
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 96-111
    4, 7, 0, 0, 2, 2, 0, 4, 0, 0, 0, 0, 4, 5, 0, 5, // 112-127
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 128-143
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 144-159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160-175
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 176-191
    0, 2, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, // 192-207
    0, 7, 0, 0, 0, 6, 5, 5, 0, 0, 0, 0, 0, 5, 0, 5, // 208-223
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 224-239
    0, 2, 0, 0, 0, 4, 0, 6, 0, 0, 0, 0, 0, 2, 0, 2  // 240-255
};

unsigned char grid_sprite_offsets_y[256] = {
    6, 6, 6, 6, 7, 5, 6, 4, 6, 6, 6, 6, 6, 6, 6, 6, // 0-15
    0, 1, 6, 6, 0, 2, 6, 2, 6, 6, 6, 6, 1, 3, 6, 4, // 16-31
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 32-47
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 48-63
    7, 6, 6, 6, 0, 7, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, // 64-79
    0, 5, 6, 6, 0, 6, 6, 2, 6, 6, 6, 6, 1, 3, 6, 5, // 80-95
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 96-111
    3, 1, 6, 6, 3, 1, 6, 5, 6, 6, 6, 6, 1, 1, 6, 4, // 112-127
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 128-143
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 144-159
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 160-175
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 176-191
    6, 2, 6, 6, 6, 7, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, // 192-207
    6, 4, 6, 6, 6, 5, 5, 5, 6, 6, 6, 6, 6, 4, 6, 2, // 208-223
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 224-239
    6, 4, 6, 6, 6, 6, 6, 4, 6, 6, 6, 6, 6, 5, 6, 6  // 240-255
};

bool TileValid(int x, int y)
{
    return (x >= 0) and (y >= 0) and (x < CHUNK_SIZE) and (y < CHUNK_SIZE);
}

void GridChunk::AddTile(int x, int y)
{
    if (!TileValid(x, y) or tiles[x][y])
        return;

    tiles[x][y] = true;
    if (tile_sprites[x][y] != 0)
        tile_sprites[x][y] = 0;

    for (int i = 0; i < 8; i += 2)
    {
        int nX = x + grid_directions[0][i], nY = y + grid_directions[1][i];

        if (!TileValid(nX, nY) or !tiles[nX][nY])
            continue;

        tile_sprites[x][y] |= 1 << i;
        tile_sprites[nX][nY] |= 1 << ((i - 4) & 7);
    }

    for (int i = 1; i < 8; i += 2)
    {
        int nX = x + grid_directions[0][i], nY = y + grid_directions[1][i];

        if (!TileValid(nX, nY) or !tiles[nX][nY])
            continue;

        int prevI = i - 1, nextI = (i + 1) & 7, mask = (1 << prevI) | (1 << nextI);

        if (tile_sprites[x][y] & mask == mask)
            tile_sprites[x][y] |= 1 << i;

        prevI = (i + 3) & 7, nextI = (i + 5) & 7, mask = (1 << prevI) | (1 << nextI);

        if (tile_sprites[nX][nY] & mask == mask)
            tile_sprites[nX][nY] |= 1 << ((i - 4) & 7);
    }
}

void GridChunk::RemoveTile(int x, int y)
{
    if (!TileValid(x, y) or !tiles[x][y])
        return;

    tiles[x][y] = false;
    tile_sprites[x][y] = 0;

    for (int i = 0; i < 8; ++i)
    {
        int nX = x + grid_directions[0][i], nY = y + grid_directions[1][i];

        if (!TileValid(nX, nY) or !tiles[nX][nY])
            continue;

        tile_sprites[nX][nY] &= ~(1 << ((i - 4) & 7));
    }
}

GridChunk::GridChunk()
{
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            tiles[i][j] = false;
            tile_sprites[i][j] = 0;
        }
    }
}

void GridChunk::Draw()
{
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            if (!tiles[i][j])
                continue;
            Rectangle source = {static_cast<float>(grid_sprite_offsets_x[tile_sprites[i][j]] * GRID_SPRITE_WIDTH), static_cast<float>(grid_sprite_offsets_y[tile_sprites[i][j]] * GRID_SPRITE_HEIGHT), GRID_SPRITE_WIDTH, GRID_SPRITE_HEIGHT};
            Vector2 position = {static_cast<float>(GRID_SPRITE_WIDTH * i), static_cast<float>(GRID_SPRITE_HEIGHT * (-j))};
            DrawTextureRec(*texture, source, position, WHITE);
            DrawText(TextFormat("%d", tile_sprites[i][j]), GRID_SPRITE_WIDTH * i, GRID_SPRITE_HEIGHT * (-j), 12, RED);
        }
    }
}

bool GridChunk::GetTile(int x, int y)
{
    return tiles[x][y];
}

void GridChunk::SetTile(int x, int y, bool tile)
{
    if (tile)
        AddTile(x, y);
    else
        RemoveTile(x, y);
}

void GridChunk::SetTexture(const Texture *texture)
{
    this->texture = texture;
}
