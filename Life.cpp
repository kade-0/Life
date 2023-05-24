#include <iostream>
#include <raylib.h>
#include "World.h"

int main()
{
	InitWindow(1280, 720, "Life Simulation");

	DataFile d = DataFile("world.data");
	d.Deserialize();
	World w = World(d);

	bool edit = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);

			if (IsKeyReleased(KEY_F1))
				edit = !edit;

			if (edit)
			{
				DrawText("Edit mode enabled", 0, 0, 16, WHITE);
				DrawText("F2 to enter block creation", 0, 18, 12, WHITE);
			}

			w.Simulate();
		EndDrawing();
	}

	d.Seriallize();

	CloseWindow();
}