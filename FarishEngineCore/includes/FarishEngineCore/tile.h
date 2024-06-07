#ifndef TILE_H
#define TILE_H

#include <raylib.h>

struct Tile
{
    Texture2D texture;
    Rectangle sourceRec;
    Vector3 position;

    Tile() : texture{ 0 }, sourceRec{ 0, 0, 0, 0 }, position{ 0, 0, 0 } {}

    Tile& operator=(const Tile& other)
    {
        if (this != &other)
        {
            texture = other.texture;
            sourceRec = other.sourceRec;
            position = other.position;
        }
        return *this;
    }
};

#endif // !TILE_H