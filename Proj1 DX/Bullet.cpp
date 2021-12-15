#include "Bullet.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Bullet::Init()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("bullet");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.045f, Vector3(0, 0, 0), Vector3(PI / 2.f, 0, 0));
	active = false;
	mRadius = 0.5f;
	tag = "Bullet";
}

void Bullet::Update(float dTime) 
{
	if (active) 
	{
		timer += dTime;
		mModel.GetPosition() += currentVel * dTime;
	}

	if (timer >= 6) 
	{
		active = false;
		timer = 0;
	}
}

void Bullet::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	if (active)
		d3d.GetFX().Render(mModel);

}