#include "FarishEngineCore\isometricMap.h"

IsometricMap::IsometricMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize)
{
    tileMap = new Tile * [width];
    for (int i = 0; i < width; ++i)
    {
        tileMap[i] = new Tile[height];
    }
}

IsometricMap::~IsometricMap()
{
    for (int i = 0; i < width; ++i)
    {
        delete[] tileMap[i];
    }
    delete[] tileMap;
}

void IsometricMap::Draw()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (tileMap[x][y].texture.id != 0)
            {
                DrawTextureRec(tileMap[x][y].texture, tileMap[x][y].sourceRec, tileMap[x][y].position, WHITE);
            }
        }
    }
}

void IsometricMap::PlaceTile(int x, int y, const Tile& tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        tileMap[x][y] = tile;
        tileMap[x][y].position = GetIsoCoords(x, y);
    }
}

void IsometricMap::RemoveTile(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        tileMap[x][y] = Tile();  // Reset to default Tile
    }
}

Vector2 IsometricMap::GetIsoCoords(int x, int y)
{
    Vector2 isoCoords;
    isoCoords.x = (x - y) * (tileSize / 2);
    isoCoords.y = (x + y) * (tileSize / 4);

    return isoCoords;
}