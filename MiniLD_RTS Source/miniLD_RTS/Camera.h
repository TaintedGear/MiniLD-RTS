#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"

class Camera
{
public:
	Camera(int _screenWidth, int _screenHeight,
		int _levelWidth, int _levelHeight);
	~Camera();

	void Update();

	SDL_Rect GetCamera();
	float GetPosX();
	float GetPosY();
	float GetScrollSpeed();

	void SetPosX(float _posY);
	void SetPosY(float _posY);
	void SetScrollSpeed(float _scrollSpeed);
	void SetCameraBounds(int _levelWidth, int _levelHeight);

private:
	void RestrictCamera();

	int mScreenWidth,
		mScreenHeight,
		mLevelWidth,
		mLevelHeight;

	float mPosX,
		mPosY,
		mScrollSpeed;

	SDL_Rect mCamera;
};

#endif