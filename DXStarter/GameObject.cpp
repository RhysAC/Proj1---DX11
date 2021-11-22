#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() 
{
}

void GameObject::Init(MyD3D& d3d) 
{
	spr.mpTex = spr.LoadTexture(L"../bin/data/Player-Sprite-Test.dds", d3d.GetDevice());
}

void GameObject::Update() 
{
	spr.mPos = { 300, 200 };
}

void GameObject::Render(SpriteBatch& batch) 
{
	spr.Draw(batch);
}