#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "FarishEngineCore/tile.h"
#include "FarishEngineCore/isometricMap.h"

const int screenWidth = 800;
const int screenHeight = 600;
const int tileSize = 32;
const int gridWidth = 32;
const int gridHeight = 32;

Vector2 GetTilePosition(Vector2 mousePosition, int tileSize);

int main()
{
    InitWindow(screenWidth, screenHeight, "Farish Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    IsometricMap map(gridWidth, gridHeight, tileSize);

    Texture2D tileset = { 0 };
    bool tilesetLoaded = false;
    int tilesetRows, tilesetCols;
    Tile selectedTile;

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10 / camera.zoom;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10 / camera.zoom;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 10 / camera.zoom;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 10 / camera.zoom;

        camera.zoom += GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        map.Draw();

        EndMode2D();

        // GUI - Плитки
        float startX = screenWidth - 120;
        float startY = 10;
        int padding = 5;

        if (GuiButton(Rectangle { startX, startY, 100, 30 }, "Load Tileset"))
        {
            tileset = LoadTexture("../../assets/iso_tiles.png");
            if (tileset.id != 0)
            {
                tilesetLoaded = true;
                tilesetCols = tileset.width / tileSize;
                tilesetRows = tileset.height / tileSize;
            }
            else
            {
                tilesetLoaded = false;
                TraceLog(LOG_ERROR, "Failed to load tileset texture.");
            }
        }

        if (tilesetLoaded)
        {
            for (int i = 0; i < tilesetRows; i++)
            {
                for (int j = 0; j < tilesetCols; j++)
                {
                    Rectangle btnBounds = { startX + j * (tileSize + padding), startY + (i + 1) * (tileSize + padding), tileSize, tileSize };
                    Vector2 texturePos = { (float)(j * tileSize), (float)(i * tileSize) };
                    Rectangle sourceRec = { texturePos.x, texturePos.y, (float)tileSize, (float)tileSize };

                    if (GuiButton(btnBounds, ""))
                    {
                        selectedTile.texture = tileset;
                        selectedTile.sourceRec = sourceRec;
                    }

                    // Отрисовка текстуры на кнопке
                    DrawTextureRec(tileset, sourceRec, Vector2 { btnBounds.x, btnBounds.y }, WHITE);
                }
            }
        }

        // Обработка нажатия мыши для установки плитки
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tilesetLoaded)
        {
            Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
            int gridX = (mousePosition.x / (tileSize / 2) + mousePosition.y / (tileSize / 4)) / 2;
            int gridY = (mousePosition.y / (tileSize / 4) - mousePosition.x / (tileSize / 2)) / 2;
            map.PlaceTile(gridX, gridY, selectedTile);
        }

        // Обработка нажатия мыши для удаления плитки
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
            int gridX = (mousePosition.x / (tileSize / 2) + mousePosition.y / (tileSize / 4)) / 2;
            int gridY = (mousePosition.y / (tileSize / 4) - mousePosition.x / (tileSize / 2)) / 2;
            map.RemoveTile(gridX, gridY);
        }

        EndDrawing();
    }

    // Очистка ресурсов
    if (tilesetLoaded)
    {
        UnloadTexture(tileset);
    }
    CloseWindow();

    return 0;
}

Vector2 GetTilePosition(Vector2 mousePosition, int tileSize)
{
    Vector2 tilePosition;
    tilePosition.x = (floor(mousePosition.x / tileSize) * tileSize);
    tilePosition.y = (floor(mousePosition.y / tileSize) * tileSize / 2);
    return tilePosition;
}
