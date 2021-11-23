#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	void Init();
	void Update();
	void Render();
private:
	void MovePlayer();

	float speed;
};

