#include "Camera.h"

Camera::Camera( int _screenWidth, int _screenHeight,
	int _levelWidth, int _levelHeight) : mScreenWidth(_screenWidth), mScreenHeight(_screenHeight),
	mLevelWidth(_levelWidth), mLevelHeight(_levelHeight), mPosX(0.0f), mPosY(0.0f), mScrollSpeed(1.0f)
{
	mCamera.x = 0;
	mCamera.y = 0;
	mCamera.w = mScreenWidth;
	mCamera.h = mScreenHeight;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Uint8* keys = SDL_GetKeyState(NULL);

	if(keys[SDLK_UP])
	{
		mPosY -= mScrollSpeed;
	}
	if(keys[SDLK_DOWN])
	{
		mPosY += mScrollSpeed;
	}
	if(keys[SDLK_LEFT])
	{
		mPosX -= mScrollSpeed;
	}
	if(keys[SDLK_RIGHT])
	{
		mPosX += mScrollSpeed;
	}

	RestrictCamera();

	mCamera.w = mScreenWidth;
	mCamera.h = mScreenHeight;
	mCamera.x = mPosX;
	mCamera.y = mPosY;
}

void Camera::RestrictCamera()
{
	//keeps camera within the bounds of the level
	if(mPosX <= 0)
	{
		mPosX = 0;
	}
	if(mPosX >= mLevelWidth - mCamera.w)
	{
		mPosX = mLevelWidth - mCamera.w;
	}
	if(mPosY <= 0)
	{
		mPosY = 0;
	}
	if(mPosY >= mLevelHeight - mCamera.h)
	{
		mPosY = mLevelHeight - mCamera.h;
	}
}

SDL_Rect Camera::GetCamera()
{
	return mCamera;
}

float Camera::GetPosX()
{
	return mPosX;
}
float Camera::GetPosY()
{
	return mPosY;
}
float Camera::GetScrollSpeed()
{
	return mScrollSpeed;
}
void Camera::SetPosX(float _posX)
{
	mPosX = _posX;
}
void Camera::SetPosY(float _posY)
{
	mPosY = _posY;
}
void Camera::SetScrollSpeed(float _scrollSpeed)
{
	mScrollSpeed = _scrollSpeed;
}
void Camera::SetCameraBounds(int _levelWidth, int _levelHeight)
{
	mLevelWidth = _levelWidth * 32; // may change the * 32 part
	mLevelHeight = _levelHeight * 32;
}