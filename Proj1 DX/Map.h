#pragma once
#include "Model.h"
#include "Mesh.h"
#include "GameUtils.h"

class Map
{
public:
	Map(){}
	void Init(Model& m);
	void Render();

	std::vector<Model> mModels;
	enum Modelid { FLOOR, BACK_WALL, BOTTOM_WALL, LEFT_WALL, RIGHT_WALL, TOTAL = 5 };
};

