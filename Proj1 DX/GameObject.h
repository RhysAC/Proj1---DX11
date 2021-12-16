#pragma once
#include "Model.h"
#include "Mesh.h"
#include "GameUtils.h"
#include "WindowUtils.h"
#include "GeometryBuilder.h"
#include "D3D.h"
#include "Input.h"
#include "Map.h"
#include <vector>
class GameObject
{
public:
	//Default constructor
	GameObject(){}
	//A virtual update function containing nothing as this will call the derived objects Update
	virtual void Update(float dTime)
	{
		mSpeed = mSpeed;
	}
	//A virtual Render function containing nothing as this will call the derived objects Render
	virtual void Render()
	{
		mSpeed = mSpeed;
	}
	/* A function to check the collisions between all objects in the scene
	*IN : vector<GameObject*>& objects
	*OUT :
	*PRE_CONDITION : a valid vector of objects must be passed in
	*POST_CONDITION : objects will be updated depending on if they are colliding or not */
	void CheckCollision(std::vector<GameObject*>& objects);
	//A virtual Hit function containing nothing as this will call the derived objects Hit
	virtual void Hit(GameObject& other) {
		mSpeed = mSpeed;
	};
	//A virtual TakeDamage function containing nothing as this will call the derived objects TakeDamage
	virtual void TakeDamage(int damage) {
		mHealth = mHealth;
	};

	//objects model 
	Model mModel;
	//Material to be placed on model
	Material mat;
	//movement speed
	float mSpeed = 0;
	//radius for object collision
	float mRadius = 0;
	//Health of object
	int mHealth = 0;
	//is the object active 
	bool active = false;
	//is the object colliding
	bool colliding = false;
	//tag to differentiate the kinds of object. Set in objects initialise function
	std::string tag;


};

