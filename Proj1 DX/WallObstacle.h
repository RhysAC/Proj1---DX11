#pragma once
#include "GameObject.h"
#include "Player.h"
class WallObstacle : public GameObject
{
public:
	WallObstacle() {};
	void Init(Player& player);
	void Update(float dTime);
	void Render();

	Player* pPlayer = nullptr;
};

