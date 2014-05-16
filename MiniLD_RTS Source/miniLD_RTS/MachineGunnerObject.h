#ifndef MACHINE_GUNNER_OBJECT_H
#define MACHINE_GUNNER_OBJECT_H

#include "SDL.h"
#include "Camera.h"
#include "UnitObject.h"
#include "Level.h"

class MachineGunnerObject : public UnitObject
{
public:
	explicit MachineGunnerObject(SDL_Surface *sprite, SDL_Surface *markers, SDL_Surface* healthBar,
		float _posX, float _posY) : 
	UnitObject (sprite, markers, healthBar, _posX, _posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 32;
		mSheetY = 64;

		mScreenWidth = 32;
		mScreenHeight = 32;

		mShow = true;

		mAttackSpeed = 50.0f;
		mDamage = 0.7f;
		mSpeed = 1000.0f;
		mDrag = 10.0f;
		mRange = 100.0f;
		mMaxHealth = 1000.0f;
		mHealth = mMaxHealth;
	}

	~MachineGunnerObject();

	void Update( float dt, Level *level );
	void Draw(SDL_Surface* buffer, Camera *camera);

private:
};

#endif