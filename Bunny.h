#pragma once
#include "Creature.h"
class Bunny : public Creature
{
public:
	Bunny(int _x, int _y) : Creature(_x, _y)
	{
		pos.width = 16;
		pos.height = 16;
		weight = 9;
	}

	void draw() override {
		DrawRectangleRounded({pos.x,pos.y,pos.width,pos.height}, 0.8, 4, WHITE);
		DrawRectangleRounded({pos.x + (pos.width / 4),pos.y + (pos.height / 4),pos.width / 2.5f,pos.height / 2.5f}, 0.8, 4, BLACK);
		DrawRectangleRounded({ pos.x + (pos.width / 1.5f),pos.y + (pos.height / 4),pos.width / 2.5f,pos.height / 2.5f }, 0.8, 4, BLACK);
	}
};