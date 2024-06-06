#ifndef TILE_H
#define TILE_H

#include <raylib.h>

struct Tile
{
    Texture2D texture;
    Rectangle sourceRec;
    Vector2 position;

    Tile() : texture{ 0 }, sourceRec{ 0, 0, 0, 0 }, position{ 0, 0 } {}
};

#endif // !TILE_H
