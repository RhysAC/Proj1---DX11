#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() 
{
}

void GameObject::Update() 
{

}

void GameObject::Render(SpriteBatch& batch) 
{
	spr.Draw(batch);
}