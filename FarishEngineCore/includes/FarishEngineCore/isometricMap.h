#ifndef ISOMETRICMAP_H
#define ISOMETRICMAP_H

#include <raylib.h>
#include <raymath.h>
#include "FarishEngineCore\tile.h"

class IsometricMap
{
public:
    IsometricMap(int width, int height, int tileSize);
    ~IsometricMap();

    void Draw();
    void PlaceTile(int x, int y, const Tile& tile);
    void RemoveTile(int x, int y);
    Vector2 GetIsoCoords(int x, int y);

private:
    int width;
    int height;
    int tileSize;
    Tile** tileMap;
};

#endif // !ISOMETRICMAP_H