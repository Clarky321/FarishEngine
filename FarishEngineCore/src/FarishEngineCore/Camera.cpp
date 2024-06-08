#include <FarishEngineCore\Camera.h>

Camera2D InitCamera()
{
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    return camera;
}

void UpdateCamera(Camera2D& camera)
{
    if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10 / camera.zoom;
    if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10 / camera.zoom;
    if (IsKeyDown(KEY_UP)) camera.target.y -= 10 / camera.zoom;
    if (IsKeyDown(KEY_DOWN)) camera.target.y += 10 / camera.zoom;

    camera.zoom += GetMouseWheelMove() * 0.1f;
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;
}