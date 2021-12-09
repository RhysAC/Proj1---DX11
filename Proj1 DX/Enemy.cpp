#include "Enemy.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Enemy::Init(Player& player)
{
	pPlayer = &player;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("enemy");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.045f, Vector3(5, 0, 5), Vector3(-PI / 2, 0, 0));
	mSpeed = 1;
}

void Enemy::Update(float dTime) 
{
	Vector3 pos = mModel.GetPosition();
	Vector3 otherPos = pPlayer->mModel.GetPosition();
	Vector3 dir = Getdirection(pos, otherPos);
	Vector3 vel = GetCurrentVel(dir, mSpeed);
	mModel.GetPosition()+= vel * dTime;
}

void Enemy::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	d3d.GetFX().Render(mModel);
}