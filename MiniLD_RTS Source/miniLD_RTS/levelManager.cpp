#include "LevelManager.h"

LevelManager::LevelManager(SDL_Surface *tileSheet) : mCurrentLevel(0), mNewLevel(NULL)
{
	mNewLevel = new Level("Levels/levelTwoFloor.txt", "Levels/levelTwoWalls.txt", tileSheet, 50, 50);
	mLevels.push_back(mNewLevel);
}

LevelManager::~LevelManager()
{
	delete mNewLevel;
}

void LevelManager::Update( float dt )
{
	mNewLevel->Update(dt);
}

void LevelManager::Draw( SDL_Surface *buffer, Camera *camera)
{
	mNewLevel->Draw(buffer, camera);
}

Level* LevelManager::GetLevel()
{
	return mNewLevel;
}