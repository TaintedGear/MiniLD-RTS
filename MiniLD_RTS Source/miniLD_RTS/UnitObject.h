#ifndef UNITOBJECT_H
#define UNITOBJECT_H

#include "SDL.h"
#include "Camera.h"
#include "Timer.h"
#include "Level.h"
#include "PathFinder.h"
#include "PhysicsObject.h"
#include "MarkerObject.h"
#include "HealthBarObject.h"

class UnitObject : public PhysicsObject
{
public:
	UnitObject(SDL_Surface *sprite, SDL_Surface* markers, SDL_Surface* healthBar, float _posX, float _posY) : PhysicsObject
		(sprite, _posX, _posY)
	{
		mSelected = false;
		mDead = false;
		mPassive = false;

		mTargetX = 0.0f;
		mTargetY = 0.0f;
		mMoveTargetX = 0.0f;
		mMoveTargetY = 0.0f;

		mRange = 0.0f;
		mDamage = 0.0f;
		mAttackSpeed = 0.0f;
		mHealth = 0.0f;
		mMaxHealth = 0.0f;
	
		mOrderState = 0;
		mState = 0;
		mTargetObject = NULL;

		mHealthBar = new HealthBarObject( healthBar, 0.0f, 0.0f );
		mSelectionMarker = new MarkerObject(markers, mPosX, mPosY, 0);
		mMarker = new MarkerObject(markers, 0.0f, 0.0f , 0);
		mAttackMarker = new MarkerObject(markers, 0.0f, 0.0f, 32);
		mAttackMarker->SetCycle(true);
		mMarker->SetFrame(3);
		mSelectionMarker->SetFrame(0);
	}
	
	virtual ~UnitObject();

	virtual void Update(float dt, Level *level);
	virtual void Draw(SDL_Surface *buffer, Camera *camera);

	void SetSelected(bool _selected);
	void SetTargetX(float _targetX);
	void SetTargetY(float _targetY);
	void SetMoveTargetX(float _moveTargetX);
	void SetMoveTargetY(float _moveTargetY);
	void SetOrderState(int _orderState);
	void SetTargetObject(UnitObject *_target);
	void SetHealth(float _health);
	void SetDead(bool _dead);

	bool GetDead();
	bool GetSelected();
	int GetOrderState();
	float GetTargetX();
	float GetTargetY();
	float GetRange();
	float GetHealth();
	float GetDamage();
	float GetAttackSpeed();

protected:

//	PathFinder mPathFinder;

	MarkerObject *mMarker;
	MarkerObject *mSelectionMarker;
	MarkerObject *mAttackMarker;
	HealthBarObject *mHealthBar;

	Timer mTimer;

	UnitObject *mTargetObject;

	bool mSelected,
		mDead,
		mPassive;

	float mTargetX,
		mTargetY,
		mRange,
		mHealth,
		mMaxHealth,
		mDamage,
		mAttackSpeed,
		mMoveTargetX,
		mMoveTargetY;

	int mOrderState,
		mState;

	enum mOrders {NO_ORDER = 0, MOVE = 1, ATTACK = 2, GRAB = 3};
	enum mState {ALIVE = 0, DEAD = 2};

private:

	void UpdateOrderState(float dt, Level *level);
};

#endif