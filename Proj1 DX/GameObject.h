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
	GameObject(){}
	virtual void Update(float dTime)
	{
		mSpeed = mSpeed;
	}
	virtual void Render()
	{
		mSpeed = mSpeed;
	}

	void CheckCollision(std::vector<GameObject*>& objects);

	virtual void Hit(GameObject& other) {
		mSpeed = mSpeed;
	};

	Model mModel;
	Material mat;
	float mSpeed = 0;
	float mRadius = 0;
	bool active = false;
	bool colliding = false;
	std::string tag;
};

