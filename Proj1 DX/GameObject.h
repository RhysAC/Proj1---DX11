#pragma once
#include "Model.h"
#include "Mesh.h"
#include "GameUtils.h"
#include "WindowUtils.h"
#include "GeometryBuilder.h"
#include "D3D.h"
#include "Input.h"

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

	Model mModel;
	float mSpeed = 0;
	bool active = false;
};

