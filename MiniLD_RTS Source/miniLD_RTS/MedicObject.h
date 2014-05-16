#ifndef MEDIC_OBJECT_H
#define MEDIC_OBJECT_H

#include "UnitObject.h"

class MedicObject : public UnitObject
{
public:
	explicit MedicObject(SDL_Surface *sprite, SDL_Surface *markers, SDL_Surface* healthBar,
		float _posX, float _posY) : 
	UnitObject (sprite, markers, healthBar, _posX, _posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 32;
		mSheetY = 64*2;

		mScreenWidth = 32;
		mScreenHeight = 32;

		mShow = true;
		mPassive = true;

		mAttackSpeed = 100.0f;
		mDamage = 0.7f;
		mSpeed = 1000.0f;
		mDrag = 10.0f;
		mRange = 150.0f;
		mMaxHealth = 1000.0f;
		mHealth = mMaxHealth;
	}

	~MedicObject();

	void Update( float dt, Level *level );
	void Draw(SDL_Surface *buffer, Camera *camera);
private:
};

#endif