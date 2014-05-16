#ifndef HEALTH_BAR_OBJECT_H
#define HEALTH_BAR_OBJECT_H

#include "SDL.h"
#include "Utillitys.h"
#include "Camera.h"
#include "GameObject.h"

using namespace Utillitys;

class HealthBarObject : public GameObject
{
public:
	explicit HealthBarObject (SDL_Surface* _sprite, float _posX, float _posY) : 
	GameObject (_sprite, _posX, _posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 5;
		mSheetY = 0;

		mScreenWidth = 32;
		mScreenHeight = 5;

		mShow = true;
	}

	~HealthBarObject();

	void Update( float dt, float _posX, float _posY, float offset, float maxHealth, float currHealth );
	void Draw( SDL_Surface* buffer, Camera *camera);

private:

};

#endif