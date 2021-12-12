#include "WallObstacle.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void WallObstacle::Init(Player& player, Mesh& sm)
{
	pPlayer = &player;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Setup(mModel, sm, Vector3(1.5, 1, 1), Vector3(GetPosOffScreen(), 0, 40), Vector3(0, 0, 0));
	Material mat;
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	mModel.SetOverrideMat(&mat);
	mSpeed = 20;
}

void WallObstacle::Update(float dTime)
{
	mModel.GetPosition().z -= mSpeed * dTime;
	if (mModel.GetPosition().z <= -10) 
	{
		mModel.GetPosition().x = GetPosOffScreen();
		mModel.GetPosition().z = 40;
	}
}

void WallObstacle::Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	d3d.GetFX().Render(mModel);
}