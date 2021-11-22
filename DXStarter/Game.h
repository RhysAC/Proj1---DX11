#pragma once
#include <vector>

#include "D3D.h"
#include "SpriteBatch.h"
#include "GameObject.h"

class Game
{
public:
	Game(MyD3D& d3d);
	void ReleaseGame();
	void Init(MyD3D& d3d);
	void Update(float dTime, MyD3D& d3d);
	void Render(float dTime, MyD3D& d3d);
private:
	DirectX::SpriteBatch* mSpriteBatch = nullptr;
	GameObject mPlayer;	
	std::vector<GameObject> objects;
};

