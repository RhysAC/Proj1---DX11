#ifndef GAME_H
#define GAME_H

#include <future>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Input.h"
#include "Mesh.h"
#include "Model.h"
#include "singleton.h"
#include "Map.h"
#include "GameUtils.h"
#include "GameObject.h"
#include "Player.h"
#include "WallObstacle.h"
#include "Bullet.h"
#include "DataBase.h"
#include "AudioMgr.h"
#include "Energy.h"
#include <fstream>
#include <ostream>

class Game : public Singleton<Game>
{
public:
	//Default constructor and Destructor
	Game() {}
	~Game() {
		Release();
	}
	/*A function to Update logic for the game
	*IN : float Dtime, IAudioMgr* audio
	*OUT :
	*PRE_CONDITION : There must be valid objects in the vector to update. The pointer to audio must be valid
	*POST_CONDITION : Game logic will be updated  */
	void Update(float dTime);
	//Render all models active in the scene
	void Render();
	/*A function to initialise certain data for the Game
	*IN : IAudioMgr& audio
	*OUT :
	*PRE_CONDITION : game object must exist, a d3d device must be active, the pointer to audio must be valid
	*POST_CONDITION : The state will be changed to the menu screen and data will be set */
	void Initialise(IAudioMgr* audio);
	//Delete batches and set the pointers back to null
	void Release();
	//default message handler for recieving input, with an added lParam for 'Raw' input
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Enum class dictating what current stage that game is at
	enum class StateMachine {
		SPLASH_SCREEN,
		PLAY,
		GAME_OVER,
		LEADERBOARD
	};
	//Default camera position
	const DirectX::SimpleMath::Vector3 mDefCamPos = DirectX::SimpleMath::Vector3(0, 0, -2);
	//Cam position to be updated in game
	DirectX::SimpleMath::Vector3 mCamPos;
	//All the objects needed
	std::vector<GameObject*> mObjects;
	Map mMap;
	Player mPlayer;
	WallObstacle mObstacle;
	Bullet mBullet;
	Energy mEnergy;
	//Store the current state
	StateMachine mState;
private:
	//Print text 
	DirectX::SpriteBatch *mpFontBatch = nullptr;
	DirectX::SpriteFont *mpFont = nullptr;
	//Current score 
	float mScore = 0;
	//Timer to check how long a state has been active and if we can change, this avoids input causing multiple state changes
	float timer = 0;
	std::string mName;
	//Data object used for saving / loading
	DataBase mData;
	//load all models and Data saved in the data file
	void Load();
	//separate out in-game rendering
	void RenderGame();
};

#endif
