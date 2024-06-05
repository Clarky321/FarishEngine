#include <raylib.h>

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Farish Engine");

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}