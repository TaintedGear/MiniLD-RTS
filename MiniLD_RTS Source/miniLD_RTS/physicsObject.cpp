#include "PhysicsObject.h"

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update(float dt)
{
	float newVelX = 0.0f;
	float newVelY = 0.0f;
	float newPosX = 0.0f;
	float newPosY = 0.0f;

	mAccX += (mVelX * -1) * mDrag;
	mAccY += (mVelY * -1) * mDrag;

	newPosX = mPosX + mVelX * dt;
	newPosY = mPosY + mVelY * dt;

	newVelX = mVelX + mAccX * dt;
	newVelY = mVelY + mAccY * dt;

	mPosX = newPosX;
	mPosY = newPosY;
	mVelX = newVelX;
	mVelY = newVelY;
	mAccX = 0.0f;
	mAccY = 0.0f;

	GameObject::Update(dt);
}

void PhysicsObject::Draw(SDL_Surface *buffer, Camera *camera)
{
	GameObject::Draw(buffer, camera);
}

float PhysicsObject::GetAccX()
{
	return mAccX;
}
float PhysicsObject::GetAccY()
{
	return mAccY;
}
float PhysicsObject::GetSpeed()
{
	return mSpeed;
}
float PhysicsObject::GetVelX()
{
	return mVelX;
}
float PhysicsObject::GetVelY()
{
	return mVelY;
}

void PhysicsObject::SetAccX( float _accX)
{
	mAccX = _accX;
}
void PhysicsObject::SetAccY( float _accY)
{
	mAccY = _accY;
}
void PhysicsObject::SetVelX( float _velX)
{
	mVelX = _velX;
}
void PhysicsObject::SetVelY( float _velY)
{
	mVelY = _velY;
}