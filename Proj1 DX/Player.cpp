#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Player::Init(BulletMgr& mgr)
{
	pBulletMgr = &mgr;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	// Player for now 
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("suck");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.045f, Vector3(0, 0, -2), Vector3(PI / 2.f, 0, 0));
	mSpeed = 2;
}

void Player::Update(float dTime)
{
	HandleInput(dTime);
}

void Player::HandleInput(float dTime) 
{
	Vector3 pos{ mModel.GetPosition() };
	float rotation = mModel.GetRotation().y;

	if (sMKIn.IsPressed(VK_W) ||
		sMKIn.IsPressed(VK_S) ||
		sMKIn.IsPressed(VK_D) ||
		sMKIn.IsPressed(VK_A))
	{
		if (sMKIn.IsPressed(VK_W))
			pos.z += mSpeed * dTime;
		else if (sMKIn.IsPressed(VK_S))
			pos.z -= mSpeed * dTime;
		if (sMKIn.IsPressed(VK_D))
			pos.x += mSpeed * dTime;
		else if (sMKIn.IsPressed(VK_A))
			pos.x -= mSpeed * dTime;
	}

	if (sMKIn.IsPressed(VK_LEFT) ||
		sMKIn.IsPressed(VK_RIGHT))
	{
		if (sMKIn.IsPressed(VK_LEFT))
			rotation -= mSpeed * dTime;
		else if (sMKIn.IsPressed(VK_RIGHT))
			rotation += mSpeed * dTime;
	}

	Vector3 aimDirNorm = Getdirection(Vector3{ 0,0,0 }, mModel.GetPosition());
	if (sMKIn.IsPressed(VK_SPACE))
		FireBullet(pos, aimDirNorm);

	mModel.GetPosition() = pos;
	mModel.GetRotation().y = rotation;
}

void Player::FireBullet(Vector3& pos, Vector3& aimDirNorm)
{
	Bullet* b = pBulletMgr->NewBullet();
	if (b)
	{
		b->active = true;
		b->mModel.GetRotation().y = mModel.GetRotation().y;
		b->currentVel = aimDirNorm * b->maxSpeed;
		b->mModel.GetPosition() = pos;
	}
}

void Player::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	d3d.GetFX().Render(mModel);
}