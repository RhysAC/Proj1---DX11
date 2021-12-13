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
	mObstacle.Init(mPlayer, sm, mMap);
	mObjects.push_back(&mPlayer);
	mObjects.push_back(&mObstacle);
	for (Bullet& b : mBulletMgr.bullets)
		mObjects.push_back(&b);

	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
	d3d.GetFX().SetupDirectionalLight(1, true, Vector3(1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));

	mState = StateMachine::SPLASH_SCREEN;
}

void Game::Initialise()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	mPlayer.sMKIn.Initialise(WinUtil::Get().GetMainWnd(), true, false);
	mpFontBatch = new SpriteBatch(&d3d.GetDeviceCtx());
	assert(mpFontBatch);
	mpFont = new SpriteFont(&d3d.GetDevice(), L"../bin/data/fonts/Swipe.spritefont");
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
	switch (mState) 
	{
	case StateMachine::SPLASH_SCREEN:
		mCamPos = mDefCamPos;
		if (mPlayer.sMKIn.IsPressed(VK_P))
			mState = StateMachine::PLAY;
		mPlayer.MenuIdle(dTime);
		mMap.Scroll(dTime);
		break;
	case StateMachine::PLAY:
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->Update(dTime);
			mObjects[i]->CheckCollision(mObjects);
		}
		mMap.Scroll(dTime);
		mBulletMgr.Update(dTime);

		mCamPos = Vector3(mPlayer.mModel.GetPosition().x, 7, mPlayer.mModel.GetPosition().z - 10);
		if (mPlayer.mHealth <= 0) {
			mState = StateMachine::SPLASH_SCREEN;
			mMap.scrollSpeed = mMap.defScrollSpeed;
			mPlayer.ResetPlayer();
		}
		break;
	}
}

void Game::Render(float dTime)
{
	RenderGame(dTime);
}

void Game::RenderGame(float dTime)
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	WinUtil& wu = WinUtil::Get();
	d3d.BeginRender(Colours::Black);
	mpFontBatch->Begin();
	d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), mCamPos);

	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), mCamPos, mPlayer.mModel.GetPosition(), Vector3(0, 1, 0));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f * PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);

	string msg = " ";
	Vector2 scrn{ (float)wu.GetClientWidth(), (float)wu.GetClientHeight() };
	Vector2 pos = Vector2(0, 0);
	switch (mState)
	{
	case StateMachine::SPLASH_SCREEN:
		msg = "Max Velocity";
		RECT dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 5) - (dim.bottom / 2) };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::SteelBlue, 0, Vector2(100, 0), Vector2(2, 2));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 1.2f) - (dim.bottom / 2) };
		msg = "Press P To Play";
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::White, 0, Vector2(80, 0), Vector2(1, 1));
		mMap.Render();
		mPlayer.Render();
		break;
	case StateMachine::PLAY:
		mMap.Render();

		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->Render();
		}

		mBulletMgr.Render();
		break;
	}
	mpFontBatch->End();
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

