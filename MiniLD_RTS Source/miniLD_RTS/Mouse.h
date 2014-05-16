#ifndef MOUSE_H
#define MOUSE_H

#include<iostream>
#include<vector>
#include "SDL.h"
#include "Utillitys.h"
#include "Camera.h"
#include "UnitObject.h"
#include "PlayerController.h"
#include "EnemyController.h"

using std::vector;
using namespace Utillitys;

class Mouse
{
public:
	Mouse();
	~Mouse();

	void Update( SDL_Event &event, Camera *camera, PlayerController *player,
		EnemyController *enemy);
	void Draw( SDL_Surface *buffer);
private:

	void PickSelection(SDL_Event &event, Camera *camera,  PlayerController *player);
	void GroupSelection(SDL_Event &event, Camera *camera,  PlayerController *player);
	void SelectionBox(SDL_Surface* buffer, int x, int y);
	void PanCamera(Camera *camera);

	bool mMouseButtonIsDown;
	int mStartPosX,
		mStartPosY,
		mEndPosY,
		mEndPosX;


	float mWidth,
		mHeight,
		mScreenRegion,
		mGroupX,
		mGroupY,
		mSelection;

	SDL_Rect mCollisionBox;
	SDL_Rect mGroupBox;
};

#endif