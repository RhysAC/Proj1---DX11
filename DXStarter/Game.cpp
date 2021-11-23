#include "Game.h"

using namespace std;
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
	mPlayer.spr.SetTex(*mPlayer.spr.LoadTexture(L"../bin/data/Player-Sprite-Test.dds", d3d.GetDevice()), {0,0,200,200});
	objects.push_back(&mPlayer);

	for (size_t i = 0; i < objects.size(); ++i)
	{
		objects[i]->Init();
	}
}

void Game::Update(float dTime, MyD3D& d3d)
{
	for (size_t i = 0; i < objects.size(); ++i) 
	{
		objects[i]->Update();
	}
}

void Game::Render(float dTime, MyD3D& d3d)
{

	d3d.BeginRender(Vector4{ 0, 0, 0, 0 });


	mSpriteBatch->Begin();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		objects[i]->Render(*mSpriteBatch);
	}
	mSpriteBatch->End();


	d3d.EndRender();
}
