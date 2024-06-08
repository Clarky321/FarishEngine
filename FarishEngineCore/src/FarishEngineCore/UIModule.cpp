#include "FarishEngineCore\UIModule.h"

//void SetupDockSpace()
//{
//    ImGuiViewport* viewport = ImGui::GetMainViewport();
//    ImGui::SetNextWindowPos(viewport->Pos);
//    ImGui::SetNextWindowSize(viewport->Size);
//    ImGui::SetNextWindowViewport(viewport->ID);
//    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//
//    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//
//    ImGui::Begin("DockSpace Window", nullptr, windowFlags);
//    ImGui::PopStyleVar(3);
//
//    ImGuiID dockspaceID = ImGui::GetID("DockSpace");
//    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
//    ImGui::End();
//}

void DrawTilesetMenu(Texture2D& tileset, bool& tilesetLoaded, int& tilesetRows, int& tilesetCols, Tile& selectedTile, int& selectedTileIndex, int tileSize)
{
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
                ImGui::PushID(i * tilesetCols + j);
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
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
    }
    ImGui::End();
}