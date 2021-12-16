#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	//Default constructor
	Bullet(){};
	/* A function to Initialise data for the bullet
	*IN :
	*OUT :
	*PRE_CONDITION : The bullet object must exist 
	*POST_CONDITION : Data for the bullet will be set, and the model with be given a mesh */
	void Init();
	/* A function to Update the bullet
	*IN : float dTime
	*OUT :
	*PRE_CONDITION : The bullet object must exist, valid dTime must be passed 
	*POST_CONDITION : The bullet will update accordingly */
	void Update(float dTime);
	//Render changes to the bullet
	void Render();
	//Current velocity to be multiplied with max speed to give a direction of travel
	DirectX::SimpleMath::Vector3 currentVel{ 0, 0, 0 };
	float maxSpeed = 50.f;
private:
	//Timer tracks how long the bullet is active for
	float timer = 0;
};
