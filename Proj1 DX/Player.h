#pragma once
#include "GameObject.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	Player(){}
	void Init(BulletMgr& mgr);
	void Update(float dTime);
	void Render();
	void HandleInput(float dTime);
	void FireBullet(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& aimDirNorm);
	MouseAndKeys sMKIn;
	BulletMgr* pBulletMgr;
};

