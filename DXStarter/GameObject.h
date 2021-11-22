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
	void Init(std::string& tag);
	void Update();
	void Render(DirectX::SpriteBatch& batch);
	Sprite spr;

	std::string mTag;

	bool colliding;
	bool active;
	float speed;
	float radius;
};

