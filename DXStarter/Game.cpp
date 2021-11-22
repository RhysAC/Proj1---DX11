#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Game::Game(MyD3D& d3d)
{
	mSpriteBatch = new SpriteBatch(&d3d.GetDeviceCtx());
	assert(mSpriteBatch);
}

void Game::ReleaseGame()
{
	ReleaseCOM(mPlayer.spr.mpTex);
	delete mSpriteBatch;
	mSpriteBatch = nullptr;
}

void Game::Init(MyD3D& d3d)
{
	mPlayer.Init(d3d);
	objects.insert(objects.begin(), 1, mPlayer);
}

void Game::Update(float dTime, MyD3D& d3d)
{
	for (size_t i = 0; i < objects.size(); ++i) 
	{
		objects[i].Update();
	}
}

void Game::Render(float dTime, MyD3D& d3d)
{

	d3d.BeginRender(Vector4{ 0, 0, 0, 0 });


	mSpriteBatch->Begin();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		objects[i].Render(*mSpriteBatch);
	}
	mSpriteBatch->End();


	d3d.EndRender();
}
