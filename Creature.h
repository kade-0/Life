#pragma once
#include <raylib.h>
#include "WorldConstants.h"
#include "Helpers.h"

#ifndef CREATURE_INCLUDE
#define CREATURE_INCLUDE

class Creature
{
public:
	int type = 0;

	int food = 0;
	int health = 0;

	float weight = 0;
	
	float vertVelocity = 0;
	float horiVelocity = 0;

	Rectangle pos;

	Creature(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		pos.width = 0;
		pos.height = 0;
	}

	virtual	void draw() {

	}
};

#endif