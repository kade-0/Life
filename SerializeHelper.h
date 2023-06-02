#pragma once
#ifndef SERIALIZEHELPER_INCLUDE
#define SERIALIZEHELPER_INCLUDE
#include "DataFile.h"
#include "Wall.h"
class SerializeHelper {
public:
	static std::vector<Field> SerializePart(Part& p)
	{
		std::vector<Field> fields;
		fields.push_back(Field("part_create", p.tag));
		for (SemiParts& sp : p.semiParts)
		{
			fields.push_back(Field("part_add_semi",
				std::to_string(sp.p.x) +
				"," + std::to_string(sp.p.y) + 
				"," + std::to_string(sp.p.width) + 
				"," + std::to_string(sp.p.height) + 
				"," + std::to_string(sp.radius) + 
				"," + std::to_string(sp.c.r) + 
				"," + std::to_string(sp.c.g) + 
				"," + std::to_string(sp.c.b)));
		}
		fields.push_back(Field("part_end", p.tag));
		return fields;
	}

	static std::vector<Field> SerializeWall(Wall* w)
	{
		std::vector<Field> fields;
		fields.push_back(Field("wall_create", w->tag));
		fields.push_back(Field("wall_pos", 
			std::to_string(w->pos.x) +
			"," + std::to_string(w->pos.y) +
			"," + std::to_string(w->pos.width) +
			"," + std::to_string(w->pos.height)));
		fields.push_back(Field("wall_passable", w->passable ? "true" : "false"));
		fields.push_back(Field("wall_moveable", w->moveable ? "true" : "false"));
		fields.push_back(Field("wall_end", w->tag));
		return fields;
	}
};

#endif