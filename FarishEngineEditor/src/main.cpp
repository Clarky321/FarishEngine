#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui_raylib\include\imgui_impl_raylib.h>

#include "FarishEngineCore/Tile.h"
#include "FarishEngineCore/IsometricMap.h"
#include "FarishEngineCore\Camera.h"
#include "FarishEngineCore\UIModule.h"
#include "FarishEngineCore\Input.h"
#include "FarishEngineCore\Utils.h"

const int screenWidth = 800;
const int screenHeight = 600;
const int tileSize = 32;
const int gridWidth = 32;
const int gridHeight = 32;
const int maxHeight = 10; // Максимальная высота

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

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init();
    ImGui_ImplRaylib_Init();

    int selectedTileIndex = -1;

    while (!WindowShouldClose())
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();

        SetupDockSpace();

        UpdateCamera(camera);

        BeginDrawing();

        // Очистка экрана прямоугольником, заполненным цветом фона RAYWHITE
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);

        BeginMode2D(camera);
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