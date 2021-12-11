#pragma once
#include "Model.h"
#include "Mesh.h"
#include "GameUtils.h"

class Map
{
public:
	Map(){}
	void Init(Model& m, Mesh& mesh);
	void Render();
	void Scroll(float dTime);

	std::vector<Model> mModels;
	enum Modelid { FLOOR, FLOOR2, TOTAL = 2 };
};

