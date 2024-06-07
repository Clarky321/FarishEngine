#include "FarishEngineCore/IsometricMap.h"

IsometricMap::IsometricMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize)
{
    tileMap = new Tile * *[width];
    for (int i = 0; i < width; ++i)
    {
        tileMap[i] = new Tile * [height];
        for (int j = 0; j < height; ++j)
        {
            tileMap[i][j] = new Tile[10]; // Предполагаем максимальную высоту в 10 слоев
        }
    }
}

IsometricMap::~IsometricMap()
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            delete[] tileMap[i][j];
        }
        delete[] tileMap[i];
    }
    delete[] tileMap;
}

void IsometricMap::Draw()
{
    for (int z = 0; z < 10; ++z) // Изменено для рисования тайлов по уровням
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (tileMap[x][y][z].texture.id != 0)
                {
                    DrawTextureRec(tileMap[x][y][z].texture, tileMap[x][y][z].sourceRec, Vector2{ tileMap[x][y][z].position.x, tileMap[x][y][z].position.y }, WHITE);
                }
            }
        }
    }
}

void IsometricMap::PlaceTile(int x, int y, int z, const Tile& tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < 10)
    {
        tileMap[x][y][z] = tile;
        tileMap[x][y][z].position = { GetIsoCoords(x, y, z).x, GetIsoCoords(x, y, z).y, static_cast<float>(z) };
    }
}

void IsometricMap::RemoveTile(int x, int y, int z)
{
    if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < 10)
    {
        tileMap[x][y][z] = Tile();  // Сброс до значения по умолчанию
    }
}

Vector2 IsometricMap::GetIsoCoords(int x, int y, int z)
{
    Vector2 isoCoords;
    isoCoords.x = (x - y) * (tileSize / 2);
    isoCoords.y = (x + y) * (tileSize / 4) - z * (tileSize / 2);

    return isoCoords;
}