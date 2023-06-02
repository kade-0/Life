#pragma once
#include <cmath>
#include <vector>
#include "Helpers.h"
#include "Bunny.h"
#include "Wall.h"
#include "DataFile.h"
class World {
public:
	std::vector<Creature*> creatures = {};
	std::vector<Wall*> walls = {};
	std::vector<Part*> parts = {};

	DataFile df = DataFile("");

	Part* findPart(std::string tag)
	{
		for (Part* p : parts)
			if (p->tag == tag)
				return p;
		return NULL;
	}

	Wall* findWall(std::string tag)
	{
		for (Wall* w : walls)
			if (w->tag == tag)
				return w;
		return NULL;
	}

	World(DataFile& d)
	{
		df = d;


		for (Field f : df.fields)
		{
			if (f.Key == "part_create")
			{
				Part* p = new Part("");
				p->tag = f.Value;
				parts.push_back(p);
				continue;
			}
			std::vector<std::string> spl = Helper::split(f.Value, ",");
			Part* p = findPart(spl[0]);
			if (p == NULL)
				continue;
			if (f.Key == "part_add_semi")
			{
				if (spl.size() != 9)
					continue;
				Rectangle r = Rectangle(std::stof(spl[1]), std::stof(spl[2]), std::stof(spl[3]), std::stof(spl[4]));
				Color c = Color(std::stof(spl[6]), std::stof(spl[7]), std::stof(spl[8]), 255);
				p->semiParts.push_back(SemiParts(r, std::stof(spl[5]), c));
			}
		}
	}

	void Simulate()
	{
		for (Creature* c : creatures)
		{
			// Gravity
			c->vertVelocity = std::lerp(c->vertVelocity, -(WorldConstants::Gravity + c->weight), 0.25f);

			c->draw();
			c->pos.y -= c->vertVelocity * 0.05f;
			c->pos.x -= c->horiVelocity * 0.05f;
		}
	}
};