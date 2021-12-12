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
	Model m;
	Mesh& quadMesh = BuildQuad(d3d.GetMeshMgr());
	Mesh& sm = BuildCube(d3d.GetMeshMgr());
	mMap.Init(m, quadMesh);
	mPlayer.Init(mBulletMgr, sm);
	mObstacle.Init(mPlayer, sm);
	mObjects.push_back(&mPlayer);
	mObjects.push_back(&mObstacle);
	for (Bullet& b : mBulletMgr.bullets)
		mObjects.push_back(&b);

	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
	d3d.GetFX().SetupDirectionalLight(1, true, Vector3(1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
}

void Game::Initialise()
{
	mPlayer.sMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);

	Load();
}

void Game::Release()
{
}

void Game::Update(float dTime)
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->Update(dTime);
	}
	mMap.Scroll(dTime);
	mBulletMgr.Update(dTime);

	mCamPos = Vector3(mPlayer.mModel.GetPosition().x, 7, mPlayer.mModel.GetPosition().z - 10);
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

	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), mCamPos, mPlayer.mModel.GetPosition(), Vector3(0, 1, 0));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f * PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);
	
	mMap.Render();

	for (size_t i = 0; i < mObjects.size(); ++i) 
	{
		mObjects[i]->Render();
	}

	mBulletMgr.Render();

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
		mPlayer.sMKIn.MessageEvent((HRAWINPUT)lParam);
		break;
	}
	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

