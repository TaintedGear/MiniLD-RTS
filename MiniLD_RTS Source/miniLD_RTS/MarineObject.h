#ifndef MARINEOBJECT_H
#define MARINEOBJECT_H

#include "Utillitys.h"
#include "Level.h"
#include "UnitObject.h"
#include "Camera.h"

using namespace Utillitys;

class MarineObject : public UnitObject
{
public:
	explicit MarineObject(SDL_Surface *sprite, SDL_Surface *markers, SDL_Surface* healthBar,
		float _posX, float _posY) : 
	UnitObject (sprite, markers, healthBar, _posX, _posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 32;
		mSheetY = 0;

		mScreenWidth = 32;
		mScreenHeight = 32;

		mShow = true;

		mAttackSpeed = 100.0f;
		mDamage = 0.7f;
		mSpeed = 1000.0f;
		mDrag = 10.0f;
		mRange = 50.0f;
		mMaxHealth = 1000.0f;
		mHealth = mMaxHealth;
	}

	~MarineObject();

	void Update( float dt, Level *level );
	void Draw(SDL_Surface *buffer, Camera *camera);

private:

};

#endif