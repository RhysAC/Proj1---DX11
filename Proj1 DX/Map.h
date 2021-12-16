#pragma once
#include "Model.h"
#include "Mesh.h"
#include "GameUtils.h"

class Map
{
public:
	//Default Constructor
	Map(){}
	/*A function to initialise the map object
	*IN : Model& m, Mesh& sm
	*OUT :
	*PRE_CONDITION : must be passing in a valid model and mesh object
	*POST_CONDITION : the model will be assigned with the mesh that is loaded */
	void Init(Model& m, Mesh& mesh);
	//Render the map
	void Render();
	//Scroll the map at a speed * dTime
	void Scroll(float dTime);

	float scrollSpeed = 10;
	float defScrollSpeed = 10;
private:
	//All models for the map
	std::vector<Model> mModels;
	enum Modelid { FLOOR, FLOOR2, BACKGROUND, BACKGROUND2, TOTAL = 4 };
};

