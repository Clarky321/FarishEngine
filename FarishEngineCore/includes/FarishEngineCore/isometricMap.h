#ifndef ISOMETRICMAP_H
#define ISOMETRICMAP_H

#include <raylib.h>
#include <raymath.h>
#include <fstream>

#include "FarishEngineCore/Tile.h"

class IsometricMap
{
public:
    IsometricMap(int width, int height, int tileSize);
    ~IsometricMap();

    void Draw();
    void PlaceTile(int x, int y, int z, const Tile& tile);
    void RemoveTile(int x, int y, int z);
    Vector2 GetIsoCoords(int x, int y, int z);

    int GetWidth() const;
    int GetHeight() const;
    Tile*** GetTileMap() const;

    void LoadFromStream(std::istream& stream);
    void SaveToStream(std::ostream& stream) const;

private:
    int width;
    int height;
    int tileSize;
    Tile*** tileMap;  // Изменено с Tile** на Tile*** для поддержки высоты
};

#endif // !ISOMETRICMAP_H