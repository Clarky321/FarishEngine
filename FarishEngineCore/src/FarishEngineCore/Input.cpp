#include "FarishEngineCore\Input.h"
#include <raylib.h>

void HandleTilePlacement(IsometricMap& map, bool tilesetLoaded, int selectedTileIndex, const Tile& selectedTile, Vector3 tilePosition, int gridWidth, int gridHeight, int maxHeight, int currentHeight)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tilesetLoaded && selectedTileIndex != -1)
    {
        int gridX = static_cast<int>(tilePosition.x);
        int gridY = static_cast<int>(tilePosition.y);
        int gridZ = static_cast<int>(tilePosition.z);
        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight && gridZ >= 0 && gridZ < maxHeight)
        {
            map.PlaceTile(gridX, gridY, gridZ, selectedTile);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        int gridX = static_cast<int>(tilePosition.x);
        int gridY = static_cast<int>(tilePosition.y);
        int gridZ = static_cast<int>(tilePosition.z);
        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight && gridZ >= 0 && gridZ < maxHeight)
        {
            map.RemoveTile(gridX, gridY, gridZ);
        }
    }
}

void HandleHeightChange(int& currentHeight, int maxHeight)
{
    if (IsKeyPressed(KEY_W) && currentHeight < maxHeight - 1) currentHeight++;
    if (IsKeyPressed(KEY_S) && currentHeight > 0) currentHeight--;
}