#ifndef SLICEROBJECT_H
#define SLICEROBJECT_H

#include "SDL.h"
#include "Camera.h"
#include "Level.h"
#include "UnitObject.h"

class SlicerObject : public UnitObject
{
public:
	explicit SlicerObject(SDL_Surface *sprite, SDL_Surface *markers, SDL_Surface* healthBar,
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
		mSpeed = 1100.0f;
		mDrag = 10.0f;
		mRange = 25.0f;
		mMaxHealth = 1500.0f;
		mHealth = mMaxHealth;

		mAttackMarker->SetOffset(96);
	}

	~SlicerObject();

	void Update( float dt, Level *level );
	void Draw(SDL_Surface* buffer, Camera *camera);
private:

};

#endif