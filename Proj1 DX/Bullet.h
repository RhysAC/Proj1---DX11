#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(){};
	void Init(int num);
	float maxSpeed = 50.f;
	float timer = 0;
	DirectX::SimpleMath::Vector3 currentVel{ 0, 0, 0 };
};

class BulletMgr
{
public:
	BulletMgr()
	{
		bullets.insert(bullets.begin(), 7, Bullet());

		for (size_t i = 0; i < bullets.size(); ++i)
			bullets[i].Init(i);
	};

	void Update(float dTime);

	void Render();

	Bullet* NewBullet()
	{
		size_t i = 0;
		while (i < bullets.size() && bullets[i].active == true) ++i;
		if (i >= bullets.size())
			return nullptr;
		bullets[i].active = true;
		return &bullets[i];
	}
	//A vector to be populated with bullets
	std::vector<Bullet> bullets;
};
