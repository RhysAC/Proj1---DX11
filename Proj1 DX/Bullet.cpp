#include "Bullet.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Bullet::Init(int num)
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("bullet" + num);
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.045f, Vector3(0, 0, -2), Vector3(PI / 2.f, 0, 0));
}

void BulletMgr::Update(float dTime)
{
	//The bullet is moved in the direction of the normalized vector with it's velocity set
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].active)
		{
			bullets[i].timer += dTime;
			bullets[i].mModel.GetPosition() += bullets[i].currentVel * dTime;
			//If the bullet exists for too long we erase it to save on performance
			if(bullets[i].timer > 4)
			{
				bullets[i].active = false;
				bullets[i].timer = 0;
			}
		}
	}
}

void BulletMgr::Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].active)
		{
			d3d.GetFX().Render(bullets[i].mModel);
		}
	}
}