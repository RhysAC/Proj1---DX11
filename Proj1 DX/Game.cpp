#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Setup(Model& m, Mesh& source, const Vector3& scale, const Vector3& pos, const Vector3& rot)
{
	m.Initialise(source);
	m.GetScale() = scale;
	m.GetPosition() = pos;
	m.GetRotation() = rot;
}

void Setup(Model& m, Mesh& source, float scale, const Vector3& pos, const Vector3& rot)
{
	Setup(m, source, Vector3(scale, scale, scale), pos, rot);
}

void Game::Load()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	Model m;
	mModels.insert(mModels.begin(), Modelid::TOTAL, m);

	Mesh& quadMesh = BuildQuad(d3d.GetMeshMgr());
	Mesh& cubeMesh = BuildCube(d3d.GetMeshMgr());

	//quad wood floor
	Setup(mModels[Modelid::FLOOR], quadMesh, Vector3(5, 1, 4), Vector3(0, -1, -1), Vector3(0, 0, 0));
	Material mat;
	mat = mModels[Modelid::FLOOR].GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(), "floor.dds");
	mat.texture = "floor.dds";
	mModels[Modelid::FLOOR].SetOverrideMat(&mat);

	//Back wall
	Setup(mModels[Modelid::BACK_WALL], quadMesh, Vector3(5, 1, 1.75f), Vector3(0, 0.75f, 3), Vector3(-PI/2, 0, 0));
	mat.gfxData.Set(Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = d3d.GetCache().LoadTexture(&d3d.GetDevice(),"wall.dds");
	mat.texture = "wall.dds";
	mModels[Modelid::BACK_WALL].SetOverrideMat(&mat);

	//left wall
	Setup(mModels[Modelid::LEFT_WALL], quadMesh, Vector3(4, 1, 1.75f), Vector3(-5, 0.75f, -1), Vector3(-PI/2, -PI/2, 0));
	mModels[Modelid::LEFT_WALL].SetOverrideMat(&mat);

	//Right wall
	Setup(mModels[Modelid::RIGHT_WALL], quadMesh, Vector3(4, 1, 1.75f), Vector3(5, 0.75f, -1), Vector3(-PI / 2, PI / 2, 0));
	mModels[Modelid::RIGHT_WALL].SetOverrideMat(&mat);

	// Player for now 
	Mesh& sm = d3d.GetMeshMgr().CreateMesh("suck");
	sm.CreateFrom("data/two_mat_cube.fbx", d3d);
	Setup(mModels[Modelid::SUCK], sm, 0.045f, Vector3(0, 0, -2), Vector3(PI / 2.f, 0, 0));

	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
}

void Game::Initialise()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	mpFontBatch = new SpriteBatch(&d3d.GetDeviceCtx());
	assert(mpFontBatch);
	mpFont = new SpriteFont(&d3d.GetDevice(), L"../bin/data/fonts/algerian.spritefont");
	assert(mpFont);

	Load();
}

void Game::Release()
{
	delete mpFontBatch;
	mpFontBatch = nullptr;
	delete mpFont;
	mpFont = nullptr;
}

void Game::Update(float dTime)
{
	mAngle += dTime * 0.5f;

	mModels[Modelid::SUCK].GetPosition() += Vector3(0.1f, 0, 0) * dTime;
}

void Game::Render(float dTime)
{
	RenderGame(dTime);
}

void Game::RenderGame(float dTime)
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	d3d.BeginRender(Colours::Black);

	float alpha = 0.5f + sinf(mAngle * 2)*0.5f;

	d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), mCamPos);

	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), mCamPos, Vector3(0, 0, 0), Vector3(0, 1, 0));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f*PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);
	Matrix w = Matrix::CreateRotationY(sinf(mAngle));
	d3d.GetFX().SetPerObjConsts(d3d.GetDeviceCtx(), w);

	//main cube - forced transparency under pogram control
	Vector3 dir = Vector3(1, 0, 0);
	Matrix m = Matrix::CreateRotationY(mAngle);
	dir = dir.TransformNormal(dir, m);


	//render all models
	for (auto& mod : mModels)
		d3d.GetFX().Render(mod);

	d3d.EndRender();
}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		}
	}
	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

