#pragma once
#include "GameObject.h"
#include "Player.h"
class WallObstacle : public GameObject
{
public:
	WallObstacle() {};
	void Init(Player& player, Mesh& sm);
	void Update(float dTime);
	void Render();

	Player* pPlayer = nullptr;
};

