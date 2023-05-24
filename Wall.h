#pragma once
#ifndef WALL_INCLUDE
#define WALL_INCLUDE
#include <raylib.h>
#include <vector>

struct SemiParts {
	Rectangle p;
	float radius;

	SemiParts(Rectangle r, float rad)
	{
		p = r;
		radius = rad;
	}
};

class Part {
public:
	std::vector<SemiParts> semiParts;
	std::string tag;
};

class Wall {
public:
	Rectangle pos;
	bool passable = false;
	bool moveable = false;

	std::string tag = "";

	Part parts;

	Wall(int x, int y, int w, int h)
	{
		pos.x = x;
		pos.y = y;
		pos.width = w;
		pos.height = h;

	}

	virtual void draw()
	{

	}
};
#endif