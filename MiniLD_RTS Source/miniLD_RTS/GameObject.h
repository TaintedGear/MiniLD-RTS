#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "Camera.h"
#include "Timer.h"

class GameObject
{
public:
	GameObject(SDL_Surface* _sprite, float _posX, float _posY);
	GameObject();
	virtual ~GameObject();

	virtual void Update(float dt);
	virtual void Draw( SDL_Surface* _buffer, Camera *_camera );

	void CycleFrames(int frameStart, int frameStop, int duration);

	SDL_Rect GetCollisionBox();
	float GetPosX();
	float GetPosY();
	bool GetCollision();

	void SetShow(bool _show);
	void SetFrame(int _frame);
	void SetPosX(float _posX);
	void SetPosY(float _posY);
	void SetCollision(bool _collision);

protected:

	SDL_Surface *mSprite;

	SDL_Rect mSpriteSize,
		mScreenPosition,
		mCollisionBox;

	int mSheetWidth,
		mSheetHeight,
		mSheetY,
		mScreenWidth,
		mScreenHeight,
		mState,
		mFrame;

	float mPosX,
		mPosY;

	bool mShow,
		mFlipped,
		mCollision;

	Timer mTimer;
};

#endif