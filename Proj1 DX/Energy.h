#pragma once
#include "GameObject.h"
class Energy : public GameObject
{
public:
	//Default constructor
	Energy() {};
	/* A function to Initialise data for the energy capsules
	*IN : Mesh& sm, Map& map
	*OUT :
	*PRE_CONDITION : all passed in data must be valid and the objects must exist
	*POST_CONDITION : the player and map pointers will be set and a mesh added to the wall's model */
	void Init(Map& map);
	/* A function to Update the Wall object
	*IN : float dTime
	*OUT :
	*PRE_CONDITION : dTime must be set, The map pointer must also be valid as we get the speed of travel from that object
	*POST_CONDITION : The wall obstacle will be updated accordingly*/
	void Update(float dTime);
	/* A function to check what objects the wall has hit
	*IN : GameObject& other
	*OUT :
	*PRE_CONDITION : The passed in object must be active in the scene
	*POST_CONDITION : we will damage other objects and this one depending on what it has hit */
	void Hit(GameObject& other);
	//Render changes to the Energy object
	void Render();
private:
	Map* pMap = nullptr;

	void Move(float dTime);
};

