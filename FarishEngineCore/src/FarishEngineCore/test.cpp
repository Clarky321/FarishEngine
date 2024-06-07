//#include <raylib.h>
//#include <raymath.h>
//#define RAYGUI_IMPLEMENTATION
//#include <raygui.h>
//
//#include "FarishEngineCore/tile.h"
//#include "FarishEngineCore/isometricMap.h"
//
//const int screenWidth = 800;
//const int screenHeight = 600;
//const int tileSize = 32;
//const int gridWidth = 32;
//const int gridHeight = 32;
//const int maxHeight = 10; // Максимальная высота
//
//Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight);
//Vector2 GetIsoCoords(int x, int y, int z, int tileSize);
//
//int main()
//{
//    InitWindow(screenWidth, screenHeight, "Farish Engine");
//    SetWindowState(FLAG_WINDOW_RESIZABLE);
//
//    IsometricMap map(gridWidth, gridHeight, tileSize);
//
//    Texture2D tileset = { 0 };
//    bool tilesetLoaded = false;
//    int tilesetRows, tilesetCols;
//    Tile selectedTile;
//
//    Camera2D camera = { 0 };
//    camera.zoom = 1.0f;
//
//    int currentHeight = 0; // Текущий уровень для размещения тайлов
//
//    SetTargetFPS(60);
//
//    while (!WindowShouldClose())
//    {
//        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10 / camera.zoom;
//        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10 / camera.zoom;
//        if (IsKeyDown(KEY_UP)) camera.target.y -= 10 / camera.zoom;
//        if (IsKeyDown(KEY_DOWN)) camera.target.y += 10 / camera.zoom;
//
//        camera.zoom += GetMouseWheelMove() * 0.1f;
//        if (camera.zoom < 0.1f) camera.zoom = 0.1f;
//
//        // Изменение уровня по клавишам
//        if (IsKeyPressed(KEY_W) && currentHeight < maxHeight - 1) currentHeight++;
//        if (IsKeyPressed(KEY_S) && currentHeight > 0) currentHeight--;
//
//        BeginDrawing();
//        ClearBackground(DARKPURPLE);
//
//        BeginMode2D(camera);
//        map.Draw();
//
//        // Каркас изометрического квадратика, следующего за курсором мыши
//        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
//        Vector3 tilePosition = GetTilePosition(mousePosition, tileSize, gridWidth, gridHeight, currentHeight);
//        Vector2 isoPosition = GetIsoCoords(tilePosition.x, tilePosition.y, tilePosition.z, tileSize);
//
//        DrawLine(isoPosition.x, isoPosition.y, isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, RED);
//        DrawLine(isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y + tileSize / 2, RED);
//        DrawLine(isoPosition.x, isoPosition.y + tileSize / 2, isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, RED);
//        DrawLine(isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y, RED);
//
//        EndMode2D();
//
//        // GUI - Плитки
//        float startX = screenWidth - 120;
//        float startY = 10;
//        int padding = 5;
//
//        if (GuiButton(Rectangle{ startX, startY, 100, 30 }, "Load Tileset"))
//        {
//            tileset = LoadTexture("../../assets/isometric.png");
//            if (tileset.id != 0)
//            {
//                tilesetLoaded = true;
//                tilesetCols = tileset.width / tileSize;
//                tilesetRows = tileset.height / tileSize;
//            }
//            else
//            {
//                tilesetLoaded = false;
//                TraceLog(LOG_ERROR, "Failed to load tileset texture.");
//            }
//        }
//
//        if (tilesetLoaded)
//        {
//            for (int i = 0; i < tilesetRows; i++)
//            {
//                for (int j = 0; j < tilesetCols; j++)
//                {
//                    Rectangle btnBounds = { startX + j * (tileSize + padding), startY + (i + 1) * (tileSize + padding), tileSize, tileSize };
//                    Vector2 texturePos = { (float)(j * tileSize), (float)(i * tileSize) };
//                    Rectangle sourceRec = { texturePos.x, texturePos.y, (float)tileSize, (float)tileSize };
//
//                    if (GuiButton(btnBounds, ""))
//                    {
//                        selectedTile.texture = tileset;
//                        selectedTile.sourceRec = sourceRec;
//                    }
//
//                    // Отрисовка текстуры на кнопке
//                    DrawTextureRec(tileset, sourceRec, Vector2{ btnBounds.x, btnBounds.y }, WHITE);
//                }
//            }
//        }
//
//        // Обработка нажатия мыши для установки плитки
//        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tilesetLoaded)
//        {
//            int gridX = static_cast<int>(tilePosition.x);
//            int gridY = static_cast<int>(tilePosition.y);
//            int gridZ = static_cast<int>(tilePosition.z);
//            if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight && gridZ >= 0 && gridZ < maxHeight)
//            {
//                map.PlaceTile(gridX, gridY, gridZ, selectedTile);
//            }
//        }
//
//        // Обработка нажатия мыши для удаления плитки
//        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
//        {
//            int gridX = static_cast<int>(tilePosition.x);
//            int gridY = static_cast<int>(tilePosition.y);
//            int gridZ = static_cast<int>(tilePosition.z);
//            if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight && gridZ >= 0 && gridZ < maxHeight)
//            {
//                map.RemoveTile(gridX, gridY, gridZ);
//            }
//        }
//
//        EndDrawing();
//    }
//
//    // Очистка ресурсов
//    if (tilesetLoaded)
//    {
//        UnloadTexture(tileset);
//    }
//    CloseWindow();
//
//    return 0;
//}
//
//Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight)
//{
//    Vector3 tilePosition;
//
//    // Конвертируем экранные координаты в координаты изометрической сетки
//    float mapX = mousePosition.x / (tileSize / 2);
//    float mapY = mousePosition.y / (tileSize / 4);
//
//    tilePosition.x = (mapY + mapX) / 2;
//    tilePosition.y = (mapY - mapX) / 2;
//    tilePosition.z = currentHeight; // Используем текущий уровень для плитки
//
//    // Привязка к сетке
//    tilePosition.x = floor(tilePosition.x);
//    tilePosition.y = floor(tilePosition.y);
//
//    return tilePosition;
//}
//
//Vector2 GetIsoCoords(int x, int y, int z, int tileSize)
//{
//    Vector2 isoCoords;
//    isoCoords.x = (x - y) * (tileSize / 2);
//    isoCoords.y = (x + y) * (tileSize / 4) - z * (tileSize / 2);
//
//    return isoCoords;
//}