#include <iostream>
#include <raylib.h>
#include "World.h"
#include "SerializeHelper.h"

int main()
{
	InitWindow(1280, 720, "Life Simulation");

	DataFile d = DataFile("world.data");
	d.Deserialize();
	World w = World(d);

	bool edit = false;
	bool blockCreation = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);

			if (IsKeyReleased(KEY_F1))
				edit = !edit;
			if (IsKeyReleased(KEY_F2) && edit)
				blockCreation = !blockCreation;

			if (edit)
			{
				DrawText("Edit mode enabled", 0, 0, 16, WHITE);

				if (blockCreation)
				{
					static Part tempPart = Part("default_tag");
					static SemiParts semipart = SemiParts({0,0,0,0}, 0, WHITE);
					DrawText("Block Creation", 0, 18, 24, WHITE);
					DrawText(("Tag: " + tempPart.tag).c_str(), 0, 42, 16, WHITE);
					DrawText(("Semiparts: " + std::to_string(tempPart.semiParts.size())).c_str(), 0, 58, 16, WHITE);
					DrawText("Press S to save", 0, 74, 16, WHITE);
					Vector2 mousePos = GetMousePosition();
					if (IsMouseButtonPressed(0))
					{
						if (IsKeyPressed(KEY_LEFT_CONTROL))
						{
							// find semi part and select it (todo)
						}
						semipart.p.x = mousePos.x;
						semipart.p.y = mousePos.y;
					}
					if (IsMouseButtonDown(0))
					{
						semipart.p.width = std::abs(mousePos.x - semipart.p.x);
						semipart.p.height = std::abs(mousePos.y - semipart.p.y);
					}
					if (IsMouseButtonReleased(0))
					{
						tempPart.semiParts.push_back(semipart);
					}

					if (IsKeyPressed(KEY_S))
					{
						w.df.fields.clear();
						for (Field f : SerializeHelper::SerializePart(tempPart))
							w.df.fields.push_back(f);
						w.df.Seriallize();
					}

					DrawRectangleRounded(semipart.p, semipart.radius, 1, semipart.c);
					for(SemiParts& sp : tempPart.semiParts)
						DrawRectangleRounded(sp.p, sp.radius, 1, Color(sp.c.r, sp.c.g, sp.c.b, 128));
					EndDrawing();
					continue;
				}
				else
				{
					DrawText("F2 to enter block creation", 0, 18, 12, WHITE);
				}
			}

			w.Simulate();
		EndDrawing();
	}

	d.Seriallize();

	CloseWindow();
}