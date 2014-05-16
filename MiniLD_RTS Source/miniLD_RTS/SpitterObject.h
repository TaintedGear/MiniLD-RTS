#ifndef SPITTER_OBJECT_H
#define SPITTER_OBJECT_H

#include "SDL.h"
#include "Camera.h"
#include "Level.h"
#include "UnitObject.h"

class SpitterObject : public UnitObject
{
public:

	explicit SpitterObject(SDL_Surface *sprite, SDL_Surface *markers, SDL_Surface* healthBar,
		float _posX, float _posY) : 
	UnitObject (sprite, markers, healthBar, _posX, _posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 32;
		mSheetY = 64;

		mScreenWidth = 32;
		mScreenHeight = 32;

		mShow = true;

		mAttackSpeed = 100.0f;
		mDamage = 0.5f;
		mSpeed = 1000.0f;
		mDrag = 10.0f;
		mRange = 100.0f;
		mMaxHealth = 1000.0f;
		mHealth = mMaxHealth;

		mAttackMarker->SetOffset(64);
	}

	~SpitterObject();

	void Update( float dt, Level *level );
	void Draw ( SDL_Surface* buffer, Camera *camera);

private:


};

#endif