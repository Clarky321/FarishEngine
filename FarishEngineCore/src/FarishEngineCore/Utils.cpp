#include "FarishEngineCore\Utils.h"
#include <raylib.h>
#include <raymath.h>

Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight)
{
    Vector3 tilePosition;

    float mapX = mousePosition.x / (tileSize / 2);
    float mapY = mousePosition.y / (tileSize / 4);

    tilePosition.x = (mapY + mapX) / 2;
    tilePosition.y = (mapY - mapX) / 2;
    tilePosition.z = currentHeight;

    tilePosition.x = floor(tilePosition.x);
    tilePosition.y = floor(tilePosition.y);

    return tilePosition;
}

Vector2 GetIsoCoords(int x, int y, int z, int tileSize)
{
    Vector2 isoCoords;
    isoCoords.x = (x - y) * (tileSize / 2);
    isoCoords.y = (x + y) * (tileSize / 4) - z * (tileSize / 2);

    return isoCoords;
}

void DrawIsoTileOutline(Vector2 isoPosition, int tileSize)
{
    DrawLine(isoPosition.x, isoPosition.y, isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, RED);
    DrawLine(isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y + tileSize / 2, RED);
    DrawLine(isoPosition.x, isoPosition.y + tileSize / 2, isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, RED);
    DrawLine(isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y, RED);
}