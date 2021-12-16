#include "Energy.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Energy::Init(Map& map)
{
	pMap = &map;
	MyD3D& d3d = WinUtil::Get().GetD3D();
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("energy");
	sm.CreateFrom("data/energy.obj", d3d);
	Vector3 pos = Vector3(GetPosOffScreen(), -0.5, 60);
	if (colliding) 
	{
		pos = Vector3(GetPosOffScreen(), -0.5, 60);
	}
	Setup(mModel, sm, 0.2f, pos, Vector3(0, 0, 0));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "player.dds");
	mModel.SetOverrideMat(&mat);
	tag = "Energy";
	mRadius = 1.8f;
	active = true;
}

void Energy::Update(float dTime)
{
	Move(dTime);
}

void Energy::Move(float dTime)
{
	assert(pMap);
	//Move the walls at the same rate the floor of the map moves
	mModel.GetPosition().z -= pMap->scrollSpeed * dTime;
	mModel.GetRotation().y += 3 * dTime;
	//If the object exits the back of the screen
	if (mModel.GetPosition().z <= -5)
	{
		//make it active in case it has collided and become inactive
		active = true;
		//Get a new position for it to spawn off screen back at the front
		mModel.GetPosition().x = GetPosOffScreen();
		mModel.GetPosition().z = 60;
		if (colliding) 
		{
			mModel.GetPosition().x = GetPosOffScreen();
		}
	}
}

void Energy::Hit(GameObject& other)
{
	if (other.tag == "Player")
	{
		pMap->scrollSpeed += 1;
		active = false;
	}
}

void Energy::Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	if (active)
		d3d.GetFX().Render(mModel);
}