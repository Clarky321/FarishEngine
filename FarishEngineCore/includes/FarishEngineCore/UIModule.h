#ifndef UIMODULE_H
#define UIMODULE_H

#include <raylib.h>
#include <imgui.h>
#include "FarishEngineCore\Tile.h"

void SetupDockSpace();
void DrawTilesetMenu(Texture2D& tileset, bool& tilesetLoaded, int& tilesetRows, int& tilesetCols, Tile& selectedTile, int& selectedTileIndex, int tileSize);

#endif // !MENU_H