#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(){}
	void Init();
	void Update(float dTime);
	void Render();
	void HandleInput(float dTime);
	MouseAndKeys sMKIn;
};

