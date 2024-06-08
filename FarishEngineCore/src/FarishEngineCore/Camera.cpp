#include "FarishEngineCore/Camera.h"

Camera2D InitCamera()
{
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;  // �������������� �������� ������
    camera.offset = Vector2 { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };  // ���������� ������
    return camera;
}

void UpdateCamera(Camera2D& camera, int& rotationState)
{
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10 / camera.zoom;
    if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10 / camera.zoom;
    if (IsKeyDown(KEY_UP)) camera.target.y -= 10 / camera.zoom;
    if (IsKeyDown(KEY_DOWN)) camera.target.y += 10 / camera.zoom;

    camera.zoom += GetMouseWheelMove() * 0.1f;
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;

    if (IsKeyPressed(KEY_Q))
    {
        RotateCameraLeft(rotationState);
    }

    if (IsKeyPressed(KEY_E))
    {
        RotateCameraRight(rotationState);
    }

    // ������������� �������� ������ � ����������� �� ���������
    camera.rotation = rotationState * 90.0f;
}

void RotateCameraLeft(int& rotationState)
{
    rotationState = (rotationState - 1 + 4) % 4;  // ������������ ������ ������� �������
}

void RotateCameraRight(int& rotationState)
{
    rotationState = (rotationState + 1) % 4;  // ������������ �� ������� �������
}