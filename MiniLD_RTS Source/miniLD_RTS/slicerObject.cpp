#include "SlicerObject.h"

SlicerObject::~SlicerObject()
{
}

void SlicerObject::Update(float dt, Level *level)
{
	if(mSelected)
	{
		mSelectionMarker->SetShow(true);
		mSelectionMarker->Update(dt, mPosX, mPosY);
	}

	mFlipped = CheckFlipped(mPosX, mTargetX);

	UnitObject::Update(dt, level);
}

void SlicerObject::Draw(SDL_Surface* buffer, Camera *camera)
{
	UnitObject::Draw(buffer, camera);

}