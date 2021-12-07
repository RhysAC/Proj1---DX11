#ifndef GAME_H
#define GAME_H

#include <future>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Input.h"
#include "Mesh.h"
#include "Model.h"
#include "singleton.h"

/*
Display a small scene and spin some models around
*/
class Game : public Singleton<Game>
{
public:
	//standard stuff
	Game() {}
	~Game() {
		Release();
	}
	void Update(float dTime);
	void Render(float dTime);
	void Initialise();
	void Release();
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	const DirectX::SimpleMath::Vector3 mDefCamPos = DirectX::SimpleMath::Vector3(0, 2, -5);
	DirectX::SimpleMath::Vector3 mCamPos;

	//stick all models in a vector and use an enum to index them
	std::vector<Model> mModels;
	enum Modelid { FLOOR, BACK_WALL, BOTTOM_WALL, LEFT_WALL, RIGHT_WALL, SUCK, TOTAL=6 }; 

	MouseAndKeys sMKIn;
private:
	const float worldOffset = 0.3f;
	//printing text
	DirectX::SpriteBatch *mpFontBatch = nullptr;
	DirectX::SpriteFont *mpFont = nullptr;

	//load all models
	void Load();
	//separate out in-game rendering
	void RenderGame(float dTime);
};

#endif
