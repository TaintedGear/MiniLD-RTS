#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Camera.h"

#include "Level.h"

using std::string;
using std::vector;

class LevelManager
{
public:
	LevelManager(SDL_Surface *tileSheet);
	~LevelManager();

	void Update( float dt );
	void Draw (SDL_Surface *buffer, Camera *camera);

	Level* GetLevel();
private:

	Level *mNewLevel;
	vector<Level *> mLevels;

	int mCurrentLevel;

	/*Think of a better way to manage levels */
};

#endif