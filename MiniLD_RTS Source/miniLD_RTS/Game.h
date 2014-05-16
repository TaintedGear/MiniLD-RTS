#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <time.h>
#include "SDL.h"

#include "System.h"
#include "Utillitys.h"
#include "Timer.h"
#include "Camera.h"
#include "Mouse.h"
#include "Menu.h"
#include "LevelManager.h"
#include "PlayerController.h"
#include "EnemyController.h"

using std::string;
using std::vector;

using namespace Utillitys;

class Game
{
public:
	Game();
	~Game();

	bool Initalise();
	void Run();
	void Shutdown();

private:
	void Update(float dt);
	void Draw();

	SDL_Surface* LoadImage(std::string filename);

	int mState;
	bool mShutdown;
	float mThisTime,
		mLastTime;

	System mSystem;
	SDL_Surface *mBuffer,
		*mAlienSheet,
		*mMarineSheet,
		*mMarkerSheet,
		*mTempBackground,
		*mHealthSheet,
		*mTileSheet;

	Camera *mCamera;
	Mouse mMouse;
	Timer mDelta;
	PlayerController *mPlayer;
	EnemyController *mEnemy;
	Menu *mMenu;
	LevelManager *mLevelManager;
};

#endif