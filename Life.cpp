#include <iostream>
#include <raylib.h>
#include "World.h"
#include "SerializeHelper.h"


int align(int n, int power = 16)
{
	return (n - (n % power));
}

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
					static bool selected = false;
					static Part tempPart = Part("default_tag");
					static SemiParts semipart = SemiParts({0,0,0,0}, 0, WHITE);
					static int index = -1;
					DrawText("Block Creation", 0, 18, 24, WHITE);
					DrawText(("Tag: " + tempPart.tag).c_str(), 0, 42, 16, WHITE);
					DrawText(("Semiparts: " + std::to_string(tempPart.semiParts.size())).c_str(), 0, 58, 16, WHITE);
					DrawText(("Semipart Index: " + std::to_string(index)).c_str(), 0, 74, 16, WHITE);
					DrawText(("Color: " + std::to_string(semipart.c.r) + "," + std::to_string(semipart.c.g) + "," + std::to_string(semipart.c.b)).c_str(), 0, 92, 16, semipart.c);
					DrawText("Press S to save", 0, 108, 16, WHITE);
					Vector2 mousePos = GetMousePosition();
					Rectangle mousPosRec = { mousePos.x, mousePos.y, 16,16 };
					if (IsMouseButtonPressed(0))
					{
						semipart.p.x = align(mousePos.x);
						semipart.p.y = align(mousePos.y);
					}
					if (IsMouseButtonPressed(1) && (semipart.p.x > 0 || semipart.p.y > 0))
					{
						if (!selected)
						{
							tempPart.semiParts.push_back(semipart);
							semipart = SemiParts({ 0,0,0,0 }, 0, WHITE);
							index = tempPart.semiParts.size() - 1;
						}
						else
						{
							tempPart.semiParts[index] = semipart;
							semipart = SemiParts({ 0,0,0,0 }, 0, WHITE);
							selected = false;
							index = -1;
						}
					}

					// colors
					if (IsKeyDown(KEY_LEFT_SHIFT))
					{
						if (IsKeyPressed(KEY_ONE))
							semipart.c.r += semipart.c.r >= 255 ? -255 : 10;
						if (IsKeyPressed(KEY_TWO))
							semipart.c.g += semipart.c.g >= 255 ? -255 : 10;
						if (IsKeyPressed(KEY_THREE))
							semipart.c.b += semipart.c.b >= 255 ? -255 : 10;
					}
					if (IsKeyDown(KEY_LEFT_ALT))
					{
						if (IsKeyPressed(KEY_ONE))
							semipart.c.r -= semipart.c.r < 0 ? 255 : 10;
						if (IsKeyPressed(KEY_TWO))
							semipart.c.g -= semipart.c.g < 0 ? 255 : 10;
						if (IsKeyPressed(KEY_THREE))
							semipart.c.b -= semipart.c.b < 0 ? 255 : 10;
					}

					if (index != -1 && IsKeyPressed(KEY_D))
					{
						tempPart.semiParts.erase(tempPart.semiParts.begin() + index);
						semipart = SemiParts({ 0,0,0,0 }, 0, WHITE);
						index = -1;
					}

					if (IsKeyPressed(KEY_S))
					{
						w.df.fields.clear();
						for (SemiParts& sp : tempPart.semiParts)
							sp.c.a = 255;
						for (Field f : SerializeHelper::SerializePart(tempPart))
							w.df.fields.push_back(f);
						w.df.Seriallize();
					}

					DrawRectangleRounded(semipart.p, semipart.radius, 1, semipart.c);
					int i = 0;
					for (SemiParts& sp : tempPart.semiParts)
					{
						DrawRectangleRounded(sp.p, sp.radius, 1, Color(sp.c.r, sp.c.g, sp.c.b, sp.c.a));
						DrawText(("(" + std::to_string(static_cast<int>(sp.p.x)) + "," + std::to_string(static_cast<int>(sp.p.y)) + ")").c_str(), sp.p.x, sp.p.y - 16, 16, BLUE);
						if (CheckCollisionRecs(mousPosRec, sp.p))
						{
							sp.c.a = 220;
							if (IsKeyPressed(KEY_SPACE))
							{
								semipart = sp;
								index = i;
								selected = true;
							}
						}
						else
							sp.c.a = 128;
						i++;
					}

					if (semipart.p.x > 0 || semipart.p.y > 0)
						DrawText(("(" + std::to_string(static_cast<int>(semipart.p.x)) + "," + std::to_string(static_cast<int>(semipart.p.y)) + ")").c_str(), semipart.p.x, semipart.p.y - 16, 16, Color(200,200,200,255));

					if (IsMouseButtonDown(0))
					{
						int xDiff = mousePos.x - semipart.p.x;
						int yDiff = mousePos.y - semipart.p.y;

						if (IsKeyDown(KEY_LEFT_CONTROL))
						{
							xDiff = align(xDiff);
							yDiff = align(yDiff);
						}

						semipart.p.width = std::abs(xDiff);
						semipart.p.height = std::abs(yDiff);

						DrawText(std::to_string(static_cast<int>(semipart.p.width)).c_str(), semipart.p.x + semipart.p.width + 5, semipart.p.y, 16, GRAY);
						DrawText(std::to_string(static_cast<int>(semipart.p.height)).c_str(), semipart.p.x, semipart.p.y + semipart.p.height + 5, 16, GRAY);
					}



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