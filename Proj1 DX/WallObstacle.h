#pragma once
#include "GameObject.h"
#include "Player.h"
class WallObstacle : public GameObject
{
public:
	WallObstacle() {};
	void Init(Player& player, Mesh& sm, Map& map);
	void Update(float dTime);
	void Hit(GameObject& other);
	void Render();

	Map* pMap = nullptr;
	Player* pPlayer = nullptr;
};

