#include "WallObstacle.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void WallObstacle::Init(Player& player)
{
	pPlayer = &player;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("enemy");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.1f, Vector3(0, 0, 40), Vector3(-PI / 2, 0, 0));
	mSpeed = 1;
}

void WallObstacle::Update(float dTime)
{
	mModel.GetPosition().z -= 20 * dTime;
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