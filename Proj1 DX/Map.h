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

	float scrollSpeed = 10;
	std::vector<Model> mModels;
	enum Modelid { FLOOR, FLOOR2, BACKGROUND, BACKGROUND2, TOTAL = 4 };
};

