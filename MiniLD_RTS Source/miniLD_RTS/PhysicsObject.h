#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "SDL.h"
#include "Utillitys.h"
#include "GameObject.h"
#include "Camera.h"

using namespace Utillitys;


class PhysicsObject : public GameObject
{
public:
	explicit PhysicsObject(SDL_Surface* sprite, float _posX, float _posY) : GameObject
		(sprite, _posX, _posY)
	{
		mAccX = 0.0f;
		mAccY = 0.0f;
		mVelX = 0.0f;
		mVelY = 0.0f;
		mMaxVelX = 0.0f;
		mMaxVelY = 0.0f;
		mSpeed = 0.0f;
		mDrag = 0.0f;
	}
	
	virtual ~PhysicsObject();

	virtual void Update(float dt);
	virtual void Draw(SDL_Surface *buffer, Camera *camera);

	float GetAccX();
	float GetAccY();
	float GetVelX();
	float GetVelY();
	float GetSpeed();

	void SetAccX( float _accX );
	void SetAccY( float _accY );
	void SetVelX( float _velX );
	void SetVelY( float _velY );

protected:

	float mAccX,
		mAccY,
		mVelX,
		mVelY,
		mMaxVelX,
		mMaxVelY,
		mSpeed,
		mDrag;
	
};

#endif