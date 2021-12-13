#include "WallObstacle.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void WallObstacle::Init(Player& player, Mesh& sm, Map& map)
{
	pPlayer = &player;
	pMap = &map;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Setup(mModel, sm, Vector3(1.5, 1, 1), Vector3(GetPosOffScreen(), 0, 40), Vector3(0, 0, 0));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	mModel.SetOverrideMat(&mat);
	tag = "Wall";
	mRadius = 1;
	active = true;
}

void WallObstacle::Update(float dTime)
{
	mModel.GetPosition().z -= pMap->scrollSpeed * dTime;
	if (mModel.GetPosition().z <= -5) 
	{
		active = true;
		pMap->scrollSpeed += 1;
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
}

void WallObstacle::Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	if(active)
	d3d.GetFX().Render(mModel);
}