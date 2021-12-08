#include "WindowUtils.h"
#include "D3D.h"
#include "GeometryBuilder.h"
#include "Map.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Map::Init() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	Model m;
	mModels.insert(mModels.begin(), Modelid::TOTAL, m);

	Mesh& quadMesh = BuildQuad(d3d.GetMeshMgr());

	//quad wood floor
	Setup(mModels[Modelid::FLOOR], quadMesh, Vector3(5, 1, 4), Vector3(0, -1, -1), Vector3(0, 0, 0));
	Material mat;
	mat = mModels[Modelid::FLOOR].GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "floor.dds");
	mat.texture = "floor.dds";
	mModels[Modelid::FLOOR].SetOverrideMat(&mat);

	//Back wall
	Setup(mModels[Modelid::BACK_WALL], quadMesh, Vector3(5, 1, 1.75f), Vector3(0, 0.75f, 3), Vector3(-PI / 2, 0, 0));
	mat.gfxData.Set(Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "wall.dds");
	mat.texture = "wall.dds";
	mModels[Modelid::BACK_WALL].SetOverrideMat(&mat);

	//left wall
	Setup(mModels[Modelid::LEFT_WALL], quadMesh, Vector3(4, 1, 1.75f), Vector3(-5, 0.75f, -1), Vector3(-PI / 2, -PI / 2, 0));
	mModels[Modelid::LEFT_WALL].SetOverrideMat(&mat);

	//Right wall
	Setup(mModels[Modelid::RIGHT_WALL], quadMesh, Vector3(4, 1, 1.75f), Vector3(5, 0.75f, -1), Vector3(-PI / 2, PI / 2, 0));
	mModels[Modelid::RIGHT_WALL].SetOverrideMat(&mat);

	//Bottom wall
	Setup(mModels[Modelid::BOTTOM_WALL], quadMesh, Vector3(5, 1, 1.75f), Vector3(0, 0.75f, -5), Vector3(-PI / 2, PI, 0));
	mModels[Modelid::BOTTOM_WALL].SetOverrideMat(&mat);
}

void Map::Render() 
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	//render all models
	for (auto& mod : mModels)
		d3d.GetFX().Render(mod);
}
