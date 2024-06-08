#ifndef INPUT_H
#define INPUT_H

#include "FarishEngineCore\Tile.h"
#include "FarishEngineCore\IsometricMap.h"

void HandleTilePlacement(IsometricMap& map,
						 bool tilesetLoaded,
						 int selectedTileIndex,
						 const Tile& selectedTile,
						 Vector3 tilePosition,
						 int gridWidth,
						 int gridHeight,
						 int maxHeight,
						 int currentHeight);

void HandleHeightChange(int& currentHeight, int maxHeight);

#endif // !INPUT_H