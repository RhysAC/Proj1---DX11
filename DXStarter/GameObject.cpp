#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() 
{
}

void GameObject::Init(string& tag) 
{
	mTag = tag;
	spr.mPos = { 300, 200 };
}

void GameObject::Update() 
{
}

void GameObject::Render(SpriteBatch& batch) 
{
	spr.Draw(batch);
}