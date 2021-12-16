#include "WindowUtils.h"
#include "D3D.h"
#include "GeometryBuilder.h"
#include "Map.h"
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Map::Init(Model& m, Mesh& mesh) 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	//Insert models for each type in the enum
	mModels.insert(mModels.begin(), Modelid::TOTAL, m);

	//Setup the runway that the player will be moving on
	Setup(mModels[Modelid::FLOOR], mesh, Vector3(5, 1, 20), Vector3(0, -1, 0), Vector3(0, 0, 0));
	Material mat;
	mat = mModels[Modelid::FLOOR].GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(1.0f, 1.0f, 1.0f, 1), Vector4(0.9f, 0.1f, 0.1f, 1), Vector4(0.9f, 0.1f, 0.1f, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "runway.dds");
	mat.flags |= Material::ALPHA_TRANSPARENCY;
	mModels[Modelid::FLOOR].SetOverrideMat(&mat);

	Setup(mModels[Modelid::FLOOR2], mesh, Vector3(5, 1, 20), Vector3(0, -1, 40), Vector3(0, 0, 0));
	mModels[Modelid::FLOOR2].SetOverrideMat(&mat);

	//Setup the background that is below the runway
	Setup(mModels[Modelid::BACKGROUND], mesh, Vector3(30, 0, 30), Vector3(0, -3, 10), Vector3(0, 0, 0));
	mat = mModels[Modelid::BACKGROUND].GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "grid.dds");
	mModels[Modelid::BACKGROUND].SetOverrideMat(&mat);

	Setup(mModels[Modelid::BACKGROUND2], mesh, Vector3(30, 0, 30), Vector3(0, -3, 70), Vector3(0, 0, 0));
	mModels[Modelid::BACKGROUND2].SetOverrideMat(&mat);
}

void Map::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	//render all models
	for (auto& mod : mModels)
		d3d.GetFX().Render(mod);
}

void Map::Scroll(float dTime) 
{
	//Scroll the whole map
	mModels[Modelid::FLOOR].GetPosition().z -= scrollSpeed * dTime;
	mModels[Modelid::FLOOR2].GetPosition().z -= scrollSpeed * dTime;
	//The background scrolls slower to give a parallax effect
	mModels[Modelid::BACKGROUND].GetPosition().z -= 3 * dTime;
	mModels[Modelid::BACKGROUND2].GetPosition().z -= 3 * dTime;

	//If the floor leaves the screen, place it back behind the second piece of floor
	if (mModels[Modelid::FLOOR].GetPosition().z <= -20) 
	{
		mModels[Modelid::FLOOR].GetPosition().z = mModels[Modelid::FLOOR2].GetPosition().z + 40;
	}

	//Same as before but flipped, this gives the impression that the floor is never ending
	if (mModels[Modelid::FLOOR2].GetPosition().z <= -20)
	{
		mModels[Modelid::FLOOR2].GetPosition().z = mModels[Modelid::FLOOR].GetPosition().z + 40;
	}

	//Do the same for the backdrop
	if (mModels[Modelid::BACKGROUND].GetPosition().z <= -40)
	{
		mModels[Modelid::BACKGROUND].GetPosition().z = mModels[Modelid::BACKGROUND2].GetPosition().z + 60;
	}

	if (mModels[Modelid::BACKGROUND2].GetPosition().z <= -40)
	{
		mModels[Modelid::BACKGROUND2].GetPosition().z = mModels[Modelid::BACKGROUND].GetPosition().z + 60;
	}
}
