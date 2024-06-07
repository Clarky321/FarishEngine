#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight);
Vector2 GetIsoCoords(int x, int y, int z, int tileSize);
void DrawIsoTileOutline(Vector2 isoPosition, int tileSize);

#endif // !UTILS_H