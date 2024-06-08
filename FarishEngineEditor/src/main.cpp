#include <raylib.h>
#include <raymath.h>
#include <imgui.h>

#include <imgui_raylib/include/imgui_impl_raylib.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <tinyfiledialogs.h>

#include "FarishEngineCore/Tile.h"
#include "FarishEngineCore/IsometricMap.h"
#include "FarishEngineCore/Camera.h"
#include "FarishEngineCore/UIModule.h"
#include "FarishEngineCore/Input.h"
#include "FarishEngineCore/Utils.h"

const int screenWidth = 800;
const int screenHeight = 600;
const int tileSize = 32;
const int gridWidth = 32;
const int gridHeight = 32;
const int maxHeight = 10; // Максимальная высота

void DrawInfiniteGrid(Camera2D camera, int tileSize);
void LoadMap(IsometricMap& map, const char* filename);
void SaveMap(IsometricMap& map, const char* filename);

int main()
{
    InitWindow(screenWidth, screenHeight, "Farish Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    IsometricMap map(gridWidth, gridHeight, tileSize);

    Texture2D tileset = { 0 };
    bool tilesetLoaded = false;
    int tilesetRows, tilesetCols;
    Tile selectedTile;

    Camera2D camera = InitCamera();

    int currentHeight = 0;

    SetTargetFPS(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplRaylib_Init();
    ImGui_ImplOpenGL3_Init();

    int selectedTileIndex = -1;

    while (!WindowShouldClose())
    {
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        UpdateCamera(camera);

        // Меню сверху для загрузки и сохранения карты
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load Map"))
                {
                    const char* lFilterPatterns[2] = { "*.dat", "*.bin" };
                    const char* filename = tinyfd_openFileDialog("Load Map", "", 2, lFilterPatterns, NULL, 0);
                    if (filename)
                    {
                        LoadMap(map, filename);
                    }
                }
                if (ImGui::MenuItem("Save Map"))
                {
                    const char* filename = tinyfd_saveFileDialog("Save Map", "", 0, NULL, NULL);
                    if (filename)
                    {
                        SaveMap(map, filename);
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Меню слева для отображения текущего уровня
        ImGui::Begin("Height Level");
        ImGui::Text("Current Height: %d", currentHeight + 1);
        ImGui::End();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawInfiniteGrid(camera, tileSize);
        map.Draw();

        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector3 tilePosition = GetTilePosition(mousePosition, tileSize, gridWidth, gridHeight, currentHeight);
        Vector2 isoPosition = GetIsoCoords(tilePosition.x, tilePosition.y, tilePosition.z, tileSize);

        DrawIsoTileOutline(isoPosition, tileSize);

        EndMode2D();

        DrawTilesetMenu(tileset, tilesetLoaded, tilesetRows, tilesetCols, selectedTile, selectedTileIndex, tileSize);

        HandleTilePlacement(map, tilesetLoaded, selectedTileIndex, selectedTile, tilePosition, gridWidth, gridHeight, maxHeight, currentHeight);
        HandleHeightChange(currentHeight, maxHeight);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    if (tilesetLoaded)
    {
        UnloadTexture(tileset);
    }

    CloseWindow();

    return 0;
}

void DrawInfiniteGrid(Camera2D camera, int tileSize)
{
    Vector2 cameraPos = GetScreenToWorld2D(Vector2{ 0, 0 }, camera);
    Vector2 cameraEndPos = GetScreenToWorld2D(Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() }, camera);

    for (float x = cameraPos.x; x < cameraEndPos.x; x += tileSize)
    {
        for (float y = cameraPos.y; y < cameraEndPos.y; y += tileSize)
        {
            Vector2 isoPos = GetIsoCoords((int)x / tileSize, (int)y / tileSize, 0, tileSize);
            DrawLine(isoPos.x, isoPos.y, isoPos.x + tileSize, isoPos.y + tileSize / 2, LIGHTGRAY);
            DrawLine(isoPos.x, isoPos.y, isoPos.x - tileSize, isoPos.y + tileSize / 2, LIGHTGRAY);
        }
    }
}

void LoadMap(IsometricMap& map, const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        map.LoadFromStream(file);
        file.close();
    }
}

void SaveMap(IsometricMap& map, const char* filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        map.SaveToStream(file);
        file.close();
    }
}