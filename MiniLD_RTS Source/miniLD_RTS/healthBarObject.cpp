#include "HealthBarObject.h"

HealthBarObject::~HealthBarObject()
{
}

void HealthBarObject::Update( float dt,  float _posX, float _posY, float offset, float maxHealth, float currHealth  )
{
	mPosX = _posX;
	mPosY = _posY - offset;

	if (currHealth >= PercentageOf(maxHealth, 75.0f))
	{
		mFrame = 0;
	}
	else if (currHealth <= PercentageOf(maxHealth, 75.0f) && 
		(currHealth >= PercentageOf(maxHealth, 50.0f)))
	{
		mFrame = 1;
	}
	else if (currHealth <= PercentageOf(maxHealth, 50.0f) &&
		(currHealth >= PercentageOf(maxHealth, 25.0f)))
	{
		mFrame = 2;
	}
	else if(currHealth <= PercentageOf(maxHealth, 25.0f))
	{
		mFrame = 3;
	}


	GameObject::Update( dt );
}

void HealthBarObject::Draw( SDL_Surface* buffer, Camera *camera)
{
	GameObject::Draw( buffer, camera );
}