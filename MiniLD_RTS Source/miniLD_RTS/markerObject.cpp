#include "MarkerObject.h"

MarkerObject::~MarkerObject()
{
}

void MarkerObject::Update( float dt, float targetPosX, float targetPosY )
{
	mSheetY = mOffset;
	mPosX = targetPosX;
	mPosY = targetPosY;

	if(mCycle)
	{
		CycleFrames(0, 4, 100);
	}

	GameObject::Update(dt);
}

void MarkerObject::Draw(SDL_Surface *buffer, Camera *camera)
{
	GameObject::Draw(buffer, camera);
}

void MarkerObject::SetCycle(bool _cycle)
{
	mCycle = _cycle;
}

void MarkerObject::SetOffset(int _offset)
{
	mOffset = _offset;
}