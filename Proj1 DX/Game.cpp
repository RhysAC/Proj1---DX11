#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Game::Load()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();

	mMap.Init();
	Model m;
	mModels.insert(mModels.begin(), Modelid::TOTAL, m);

	Mesh& cubeMesh = BuildCube(d3d.GetMeshMgr());

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
	sMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);

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
	Vector2 mouse{ Game::sMKIn.GetMousePos(true) };
	Vector3 pos{ mModels[Modelid::SUCK].GetPosition() };
	float rotation = mModels[Modelid::SUCK].GetRotation().y;

	if (Game::sMKIn.IsPressed(VK_W) ||
		Game::sMKIn.IsPressed(VK_S) ||
		Game::sMKIn.IsPressed(VK_D) ||
		Game::sMKIn.IsPressed(VK_A))
	{
		if (Game::sMKIn.IsPressed(VK_W))
			pos.z += 1 * dTime;
		else if (Game::sMKIn.IsPressed(VK_S))
			pos.z -= 1 * dTime;
		if (Game::sMKIn.IsPressed(VK_D))
			pos.x += 1 * dTime;
		else if (Game::sMKIn.IsPressed(VK_A))
			pos.x -= 1 * dTime;
	}

	if (Game::sMKIn.IsPressed(VK_LEFT) ||
		Game::sMKIn.IsPressed(VK_RIGHT)) 
	{
		if (Game::sMKIn.IsPressed(VK_LEFT))
			rotation -= 2 * dTime;
		else if (Game::sMKIn.IsPressed(VK_RIGHT))
			rotation += 2 * dTime;
	}

	/*if (pos.z >= mModels[Modelid::BACK_WALL].GetPosition().z - worldOffset)
		pos.z = mModels[Modelid::BACK_WALL].GetPosition().z -worldOffset;
	if (pos.z <= mModels[Modelid::BOTTOM_WALL].GetPosition().z + worldOffset)
		pos.z = mModels[Modelid::BOTTOM_WALL].GetPosition().z + worldOffset;
	if (pos.x <= mModels[Modelid::LEFT_WALL].GetPosition().x + worldOffset)
		pos.x = mModels[Modelid::LEFT_WALL].GetPosition().x + worldOffset;
	if (pos.x >= mModels[Modelid::RIGHT_WALL].GetPosition().x - worldOffset)
		pos.x = mModels[Modelid::RIGHT_WALL].GetPosition().x - worldOffset;*/

	mCamPos = Vector3(pos.x, 15, pos.z - 2);
	mModels[Modelid::SUCK].GetPosition() = pos;
	mModels[Modelid::SUCK].GetRotation().y = rotation;
}

void Game::Render(float dTime)
{
	RenderGame(dTime);
}

void Game::RenderGame(float dTime)
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	d3d.BeginRender(Colours::Black);

	d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), mCamPos);

	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), mCamPos, mModels[Modelid::SUCK].GetPosition(), Vector3(0, 1, 0));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f * PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);


	//render all models
	for (auto& mod : mModels)
		d3d.GetFX().Render(mod);

	mMap.Render();

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
	case WM_INPUT:
		Game::sMKIn.MessageEvent((HRAWINPUT)lParam);
		break;
	}
	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

