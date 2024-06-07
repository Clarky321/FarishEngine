#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_raylib.h>

#include "FarishEngineCore/tile.h"
#include "FarishEngineCore/isometricMap.h"

const int screenWidth = 800;
const int screenHeight = 600;
const int tileSize = 32;
const int gridWidth = 32;
const int gridHeight = 32;
const int maxHeight = 10; // ������������ ������

Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight);
Vector2 GetIsoCoords(int x, int y, int z, int tileSize);

int main()
{
    InitWindow(screenWidth, screenHeight, "Farish Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    IsometricMap map(gridWidth, gridHeight, tileSize);

    Texture2D tileset = { 0 };
    bool tilesetLoaded = false;
    int tilesetRows, tilesetCols;
    Tile selectedTile; // ������������� ��������� Tile �� ���������

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    int currentHeight = 0; // ������� ������� ��� ���������� ������

    SetTargetFPS(60);

    // ������������� ImGui
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplRaylib_Init();

    int selectedTileIndex = -1;

    while (!WindowShouldClose())
    {
        // ��������� ����� ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();

        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10 / camera.zoom;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10 / camera.zoom;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 10 / camera.zoom;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 10 / camera.zoom;

        camera.zoom += GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        BeginDrawing();
        ClearBackground(DARKPURPLE);

        BeginMode2D(camera);
        map.Draw();

        // ������ ��������������� ����������, ���������� �� �������� ����
        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector3 tilePosition = GetTilePosition(mousePosition, tileSize, gridWidth, gridHeight, currentHeight);
        Vector2 isoPosition = GetIsoCoords(tilePosition.x, tilePosition.y, tilePosition.z, tileSize);

        DrawLine(isoPosition.x, isoPosition.y, isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, RED);
        DrawLine(isoPosition.x + tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y + tileSize / 2, RED);
        DrawLine(isoPosition.x, isoPosition.y + tileSize / 2, isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, RED);
        DrawLine(isoPosition.x - tileSize / 2, isoPosition.y + tileSize / 4, isoPosition.x, isoPosition.y, RED);

        EndMode2D();

        // ���� ImGui
        ImGui::Begin("Tileset Menu");
        if (ImGui::Button("Load Tileset"))
        {
            tileset = LoadTexture("../../assets/isometric.png");
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
            ImGui::Text("Select a tile:");
            for (int i = 0; i < tilesetRows; i++)
            {
                for (int j = 0; j < tilesetCols; j++)
                {
                    ImVec2 uv0 = ImVec2((float)j * tileSize / tileset.width, (float)i * tileSize / tileset.height);
                    ImVec2 uv1 = ImVec2((float)(j + 1) * tileSize / tileset.width, (float)(i + 1) * tileSize / tileset.height);
                    ImGui::PushID(i * tilesetCols + j); // ��������� ��� ������������ ID ������
                    if (ImGui::ImageButton((void*)(intptr_t)tileset.id, ImVec2((float)tileSize, (float)tileSize), uv0, uv1))
                    {
                        selectedTile.texture = tileset;
                        selectedTile.sourceRec = { (float)(j * tileSize), (float)(i * tileSize), (float)tileSize, (float)tileSize };
                        selectedTileIndex = i * tilesetCols + j;
                    }
                    if (selectedTileIndex == i * tilesetCols + j)
                    {
                        ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
                    }
                    ImGui::PopID(); // �������� ����������� ID
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }
        }
        ImGui::End();

        // ��������� ������� ���� ��� ��������� ������
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

        // ��������� ������� ���� ��� �������� ������
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

        // ��������� ������ ��� ��������� ������
        if (IsKeyPressed(KEY_W) && currentHeight < maxHeight - 1) currentHeight++;
        if (IsKeyPressed(KEY_S) && currentHeight > 0) currentHeight--;

        // ���������� ImGui ����������
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    // ������� �������� ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    // ������� ��������
    if (tilesetLoaded)
    {
        UnloadTexture(tileset);
    }

    CloseWindow();

    return 0;
}

Vector3 GetTilePosition(Vector2 mousePosition, int tileSize, int mapWidth, int mapHeight, int currentHeight)
{
    Vector3 tilePosition;

    // ������������ �������� ���������� � ���������� �������������� �����
    float mapX = mousePosition.x / (tileSize / 2);
    float mapY = mousePosition.y / (tileSize / 4);

    tilePosition.x = (mapY + mapX) / 2;
    tilePosition.y = (mapY - mapX) / 2;
    tilePosition.z = currentHeight; // ���������� ������� ������� ��� ������

    // �������� � �����
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