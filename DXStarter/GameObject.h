#pragma once
#include <vector>
#include <string>
#include "Sprite.h"
#include "SpriteBatch.h"
#include "D3D.h"

class GameObject
{
public:
	GameObject();
	virtual void Init() {};
	virtual void Update();
	void Render(DirectX::SpriteBatch& batch);
	Sprite spr;

	int mID;

	bool colliding;
	bool active;
	float speed;
	float radius;
};

