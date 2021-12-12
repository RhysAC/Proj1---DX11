#pragma once
#include "GameObject.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	Player(){}
	void Init(BulletMgr& mgr, Mesh& sm);
	void Update(float dTime);
	void Render();
	void HandleInput(float dTime);
	void FireBullet(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& aimDirNorm);
	void Hit(GameObject& other);
	MouseAndKeys sMKIn;
	BulletMgr* pBulletMgr = nullptr;
};

