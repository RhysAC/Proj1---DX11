#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Player::Init() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& cubeMesh = BuildCube(d3d.GetMeshMgr());
	// Player for now 
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("suck");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModel, sm, 0.045f, Vector3(0, 0, -2), Vector3(PI / 2.f, 0, 0));
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
			pos.z += 1 * dTime;
		else if (sMKIn.IsPressed(VK_S))
			pos.z -= 1 * dTime;
		if (sMKIn.IsPressed(VK_D))
			pos.x += 1 * dTime;
		else if (sMKIn.IsPressed(VK_A))
			pos.x -= 1 * dTime;
	}

	if (sMKIn.IsPressed(VK_LEFT) ||
		sMKIn.IsPressed(VK_RIGHT))
	{
		if (sMKIn.IsPressed(VK_LEFT))
			rotation -= 2 * dTime;
		else if (sMKIn.IsPressed(VK_RIGHT))
			rotation += 2 * dTime;
	}

	mModel.GetPosition() = pos;
	mModel.GetRotation().y = rotation;
}

void Player::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	d3d.GetFX().Render(mModel);
}