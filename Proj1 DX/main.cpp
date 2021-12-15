#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include <ctime>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;



LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
	case WM_INPUT:
		return Game::Get().WindowsMssgHandler(hwnd, msg, wParam, lParam);
	}
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}



//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	srand(time(NULL));
	int w(1024), h(768);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Max Velocity", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D())
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	//Set path for assets for ease later in the program
	d3d.GetCache().SetAssetPath("data/");

	Game game;
	game.Initialise();

	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && dTime > 0)
		{
			game.Update(dTime);
			game.Render();
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
	}
	game.Release();
	d3d.ReleaseD3D(true);
	return 0;
}
