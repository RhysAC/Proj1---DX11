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

	mModels.insert(mModels.begin(), Modelid::TOTAL, m);

	//quad wood floor
	Setup(mModels[Modelid::FLOOR], mesh, Vector3(5, 1, 20), Vector3(0, -1, 0), Vector3(0, 0, 0));
	Material mat;
	mat = mModels[Modelid::FLOOR].GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "floor.dds");
	mat.texture = "floor.dds";
	mModels[Modelid::FLOOR].SetOverrideMat(&mat);

	Setup(mModels[Modelid::FLOOR2], mesh, Vector3(5, 1, 20), Vector3(0, -1, 40), Vector3(0, 0, 0));
	mModels[Modelid::FLOOR2].SetOverrideMat(&mat);
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
	mModels[Modelid::FLOOR].GetPosition().z -= 20 * dTime;
	mModels[Modelid::FLOOR2].GetPosition().z -= 20 * dTime;

	if (mModels[Modelid::FLOOR].GetPosition().z <= -20) 
	{
		mModels[Modelid::FLOOR].GetPosition().z = mModels[Modelid::FLOOR2].GetPosition().z + 40;
	}

	if (mModels[Modelid::FLOOR2].GetPosition().z <= -20)
	{
		mModels[Modelid::FLOOR2].GetPosition().z = mModels[Modelid::FLOOR].GetPosition().z + 40;
	}
}
