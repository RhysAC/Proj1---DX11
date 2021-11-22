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
	void Init(MyD3D& d3d);
	void Update();
	void Render(DirectX::SpriteBatch& batch);
	Sprite spr;

	std::string tag;

	bool colliding;
	bool active;
	float speed;
	float radius;
};

