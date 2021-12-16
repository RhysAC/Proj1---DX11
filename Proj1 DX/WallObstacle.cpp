#include "WallObstacle.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void WallObstacle::Init(Mesh& sm, Map& map)
{
	pMap = &map;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Setup(mModel, sm, Vector3(2, 1, 1), Vector3(GetPosOffScreen(), 0, 40), Vector3(0, 0, 0));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	mModel.SetOverrideMat(&mat);
	tag = "Wall";
	mRadius = 1.5f;
	active = true;
}

void WallObstacle::Update(float dTime)
{
	Move(dTime);
}

void WallObstacle::Move(float dTime)
{
	assert(pMap);
	//Move the walls at the same rate the floor of the map moves
	mModel.GetPosition().z -= pMap->scrollSpeed * dTime;
	//If the object exits the back of the screen
	if (mModel.GetPosition().z <= -5)
	{
		//make it active in case it has collided and become inactive
		active = true;
		//Get a new position for it to spawn off screen back at the front
		mModel.GetPosition().x = GetPosOffScreen();
		mModel.GetPosition().z = 40;
	}
}

void WallObstacle::Hit(GameObject& other)
{
	if (other.tag == "Player")
	{
		other.TakeDamage(1);
		active = false;
	}

	if (other.tag == "Bullet") 
	{
		active = false;
	}
}

void WallObstacle::Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	if(active)
	d3d.GetFX().Render(mModel);
}