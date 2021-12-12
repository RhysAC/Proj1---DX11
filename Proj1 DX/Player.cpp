#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace CONSTANTS 
{
	const float LEFT_BOUNDS = -4;
	const float RIGHT_BOUNDS = 4;
}

void Player::Init(BulletMgr& mgr, Mesh& sm)
{
	pBulletMgr = &mgr;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	// Player for now 
	Setup(mModel, sm, Vector3(0.5, 0.5, 0.5), Vector3(0, 0, 5), Vector3(0, 0, 0));
	Material mat;
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "player.dds");
	mModel.SetOverrideMat(&mat);
	mSpeed = 5;
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
		sMKIn.IsPressed(VK_D) ||
		sMKIn.IsPressed(VK_A))
	{
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

	if (pos.x <= CONSTANTS::LEFT_BOUNDS)
		pos.x = CONSTANTS::LEFT_BOUNDS;
	if (pos.x >= CONSTANTS::RIGHT_BOUNDS)
		pos.x = CONSTANTS::RIGHT_BOUNDS;


	if (sMKIn.IsPressed(VK_SPACE))
		FireBullet(pos, Vector3{ 0,0,1});

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