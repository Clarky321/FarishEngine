#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

Camera2D InitCamera();
void UpdateCamera(Camera2D& camera, int& rotationState);
void RotateCameraLeft(int& rotationState);
void RotateCameraRight(int& rotationState);

#endif // !CAMERA_H