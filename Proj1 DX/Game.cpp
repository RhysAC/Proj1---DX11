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
	//Quad for the map
	Mesh& quadMesh = BuildQuad(d3d.GetMeshMgr());
	//Cube for the walls and player
	Mesh& sm = BuildCube(d3d.GetMeshMgr());

	mMap.Init(m, quadMesh);
	mBullet.Init();
	mPlayer.Init(mBullet, sm);
	mObstacle.Init(mPlayer, sm, mMap);

	//Add objects to the GameObject vector
	mObjects.push_back(&mPlayer);
	mObjects.push_back(&mObstacle);
	mObjects.push_back(&mBullet);

	//Set up 2 directional lights forming an 'X' to light both sides of the scene
	d3d.GetFX().SetupDirectionalLight(0, true, Vector3(-1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));
	d3d.GetFX().SetupDirectionalLight(1, true, Vector3(1, -3.f, 2), Vector3(0.47f, 0.47f, 0.47f), Vector3(0.15f, 0.15f, 0.15f), Vector3(0.25f, 0.25f, 0.25f));

	//Change state to start screen
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
	timer += dTime;
	switch (mState) 
	{
	case StateMachine::SPLASH_SCREEN:
		mCamPos = mDefCamPos;
		if (mPlayer.sMKIn.IsPressed(VK_P))
		{
			mState = StateMachine::PLAY;
		}
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
		mScore = mMap.scrollSpeed;
		mCamPos = Vector3(mPlayer.mModel.GetPosition().x, 7, mPlayer.mModel.GetPosition().z - 10);
		//If the player dies go to the game over screen and reset values for when they play again
		if (mPlayer.mHealth <= 0) {
			mState = StateMachine::GAME_OVER;
			mMap.scrollSpeed = mMap.defScrollSpeed;
			mPlayer.ResetPlayer();
		}
		break;
	case StateMachine::GAME_OVER:
		mCamPos = Vector3(mPlayer.mModel.GetPosition().x, 10, mPlayer.mModel.GetPosition().z - 1);
		if (mPlayer.sMKIn.IsPressed(VK_SPACE))
		{
			//If the user has entered a name, save it along with their score and change the scene 
			if (mName.size() > 1) {
				mData.SaveData(mName, mScore);
				mData.RecoverData();
				mData.SortAndUpdatePlayerData();
				mState = StateMachine::LEADERBOARD;
				timer = 0;
			}
		}
		mPlayer.MenuIdle(dTime);
		break;
	case StateMachine::LEADERBOARD:
		mMap.Scroll(dTime);
		//Timer must be greater than 2 to avoid the last space bar press carrying through and changing this state
		if (mPlayer.sMKIn.IsPressed(VK_SPACE) && timer > 2)
		{
			timer = 0;
			mState = StateMachine::SPLASH_SCREEN;
		}
	}
}

void Game::Render()
{
	RenderGame();
}

void Game::RenderGame()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	WinUtil& wu = WinUtil::Get();
	d3d.BeginRender(Colours::Black);
	mpFontBatch->Begin();
	d3d.GetFX().SetPerFrameConsts(d3d.GetDeviceCtx(), mCamPos);

	//Create view with camera position set from update and the player model being the target 
	CreateViewMatrix(d3d.GetFX().GetViewMatrix(), mCamPos, mPlayer.mModel.GetPosition(), Vector3(0, 1, 0));
	CreateProjectionMatrix(d3d.GetFX().GetProjectionMatrix(), 0.25f * PI, WinUtil::Get().GetAspectRatio(), 1, 1000.f);

	//A string to be altered and display text
	string msg = " ";
	//Screen dimensions to use for rendering the text the same regardless of aspect ratio
	Vector2 scrn{ (float)wu.GetClientWidth(), (float)wu.GetClientHeight() };
	//Position for the text to be displayed
	Vector2 pos = Vector2(0, 0);
	switch (mState)
	{
	case StateMachine::SPLASH_SCREEN:
		msg = "Max Velocity";
		//The size of the text to be used to center it
		RECT dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 5) - (dim.bottom / 2) };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::SteelBlue, 0, Vector2(100, 0), Vector2(2, 2));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 1.2f) - (dim.bottom / 2) };
		msg = "Press P To Play";
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::White, 0, Vector2(60, 0), Vector2(1, 1));
		mMap.Render();
		mPlayer.Render();
		break;
	case StateMachine::PLAY:
		mMap.Render();

		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->Render();
		}
		//Show current scroll speed
		msg = "Velocity -- " + to_string(mScore).substr(0, 3);
		dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 1.2f) - (dim.bottom / 2) };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::Yellow, 0, Vector2(0, 0), Vector2(1, 1));
		break;
	case StateMachine::GAME_OVER:
		mPlayer.Render();
		//Display Name for input along with current score
		msg = mName + " - " + to_string(mScore).substr(0, 3);
		dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 5) - (dim.bottom / 2) };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::SteelBlue, 0, Vector2(80, 0), Vector2(2, 2));
		msg = "Enter Name And Press SPACE";
		dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), (scrn.y / 1.2f) - (dim.bottom / 2) };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::White, 0, Vector2(0, 0), Vector2(1, 1));
		break;
	case StateMachine::LEADERBOARD:
		mMap.Render();
		msg = "Press SPACE";
		dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
		pos = Vector2{ (scrn.x / 2) - (dim.right / 2), pos.y += 100.f };
		mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::Yellow, 0, Vector2(0, 0), Vector2(1, 1));
		//Display the highscore table in the format Name -- Score, and in descending order
		for (size_t i = 0; i < 10; ++i)
		{
			string name;
			string score;
			if (mData.mPlayerData.size() > i) {
				name = mData.mPlayerData[i].name.substr(0, 6);
				score = mData.mPlayerData[i].score;
			}
			msg = name + "   " + score;
			dim = mpFont->MeasureDrawBounds(msg.c_str(), Vector2(0, 0));
			pos = Vector2{ (scrn.x / 2) - (dim.right / 2), pos.y += 80.f};
			mpFont->DrawString(mpFontBatch, msg.c_str(), pos, Colors::White, 0, Vector2(0, 0), Vector2(1, 1));
		}
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
		if (Game::mState == StateMachine::GAME_OVER) 
		{
			//If we press BACKSPACE delete the name
			if (wParam == 8)
				mName.clear();
			//If the key is not SPACE add it to the string
			else if(wParam != 32)
				mName += wParam;
		}
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

