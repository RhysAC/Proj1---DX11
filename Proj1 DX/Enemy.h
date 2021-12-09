#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : public GameObject
{
public:
	Enemy() {};
	void Init(Player& player);
	void Update(float dTime);
	void Render();

	Player* pPlayer = nullptr;
};

