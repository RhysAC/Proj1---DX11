#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace CONSTANTS 
{
	//Edges of the map 
	const float LEFT_BOUNDS = -5.5f;
	const float RIGHT_BOUNDS = 5.5f;
}

void Player::Init(Bullet& bullet, Mesh& sm)
{
	pBullet = &bullet;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Setup(mModel, sm, Vector3(0.5, 0.5, 0.5), Vector3(0, 0, 5), Vector3(0, 0, 0));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "player.dds");
	mModel.SetOverrideMat(&mat);
	tag = "Player";
	active = true;
	mHealth = 3;
	mRadius = 1;
	mSpeed = 10;
}

void Player::Update(float dTime)
{
	//Set these back to 0 otherwise rotation from the Idle function gets carried through
	mModel.GetRotation().y = 0;
	mModel.GetRotation().z = 0;
	HandleInput(dTime);
	// Once we have fallen off the map reset when we reach -6;
	if (mModel.GetPosition().y <= -6) 
	{
		TakeDamage(1);
		mModel.GetPosition().y = 0;
		mModel.GetPosition().x = 0;
	}
}

void Player::HandleInput(float dTime) 
{
	Vector3 pos{ mModel.GetPosition() };

	if (sMKIn.IsPressed(VK_D) ||
		sMKIn.IsPressed(VK_A))
	{
		if (sMKIn.IsPressed(VK_D))
			pos.x += mSpeed * dTime;
		else if (sMKIn.IsPressed(VK_A))
			pos.x -= mSpeed * dTime;
	}

	// If we cross the edge of the map , make the player fall
	if (pos.x <= CONSTANTS::LEFT_BOUNDS)
		pos.y -= mSpeed * dTime;
	if (pos.x >= CONSTANTS::RIGHT_BOUNDS)
		pos.y -= mSpeed * dTime;


	if (sMKIn.IsPressed(VK_SPACE))
		FireBullet(pos, Vector3{ 0,0,1});

	mModel.GetPosition() = pos;
}

void Player::TakeDamage(int damage) 
{
	mHealth -= 1;

	if (mHealth <= 0) {
		active = false;
	}
}

void Player::MenuIdle(float dTime) 
{
	mModel.GetRotation().y += 3 * dTime;
	mModel.GetRotation().z += 1 * dTime;
}

void Player::ResetPlayer() 
{
	mModel.GetPosition() = Vector3(0, 0, 5);
	mHealth = 3;
	active = true;
}

void Player::FireBullet(Vector3& pos, Vector3& aimDir)
{
	assert(pBullet);
	if (pBullet->active == false) 
	{
		pBullet->active = true;
		pBullet->currentVel = aimDir * pBullet->maxSpeed;
		pBullet->mModel.GetPosition() = pos;
	}
}

void Player::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	if(active)
	d3d.GetFX().Render(mModel);
}