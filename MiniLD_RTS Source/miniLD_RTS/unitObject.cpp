#include "UnitObject.h"

UnitObject::~UnitObject()
{
	if(mSelectionMarker != NULL) delete mSelectionMarker;
	if(mMarker != NULL ) delete mMarker;
	if(mAttackMarker != NULL) delete mAttackMarker;
	if(mHealthBar != NULL) delete mHealthBar;

}

void UnitObject::Update( float dt, Level *level )
{
	float tempPosX = 0.0f;
	float tempPosY = 0.0f;

	if(!mCollision)
	{
		tempPosX = mPosX;
		tempPosY = mPosY;
	}

	switch(mState)
	{
	case ALIVE:
		//If the health is below 0 then the unit is dead, switch state
		if((mHealth <= 0.0f) || (mDead))
		{
			mFrame = 4;
			mState = DEAD;
		}
		else
		{
			UpdateOrderState(dt, level);
		}

		//Update the markers if the unit has been selected
		if(mSelected)
		{
			mHealthBar->SetShow(true);
			mHealthBar->Update(dt, mPosX, mPosY, 7.5f , mMaxHealth, mHealth);

			mSelectionMarker->SetShow(true);
			mSelectionMarker->Update(dt, mPosX, mPosY);
		}

		//Have the unit face the correct direction
		mFlipped = CheckFlipped(mPosX, mTargetX);

		break;
	case DEAD:

		mSelected = false;
		mDead = true;
		mAttackMarker->SetFrame(0);
		mTargetObject = NULL;
		mTargetX = 0.0f;
		mTargetY = 0.0f;

		if(mFrame != 5)
		{
			CycleFrames(4, 5, 200);
		}

		break;
	};

	PhysicsObject::Update( dt );

	//Check collision with level tiles (THIS IS REALLY SHITTY THINK OF A BETTER WAY)
	for(unsigned int t = 0; t < level->GetWallTileAmount(); t++)
	{
		if(CheckCollision(mCollisionBox, level->GetWallTile(t)->GetCollisionBox()) && (!mCollision))
		{
			mPosX -= mVelX / 20;
			mPosY -= mVelY / 20;
			mCollision = true;
			break;
		}
		else
		{
			mCollision = false;
		}
	}

}

void UnitObject::Draw(SDL_Surface *buffer, Camera *camera)
{
	PhysicsObject::Draw(buffer, camera);

	if(!mDead)
	{
		if(mSelected)
		{
			mHealthBar->Draw(buffer, camera);
			mMarker->Draw(buffer, camera);
			mSelectionMarker->Draw(buffer, camera);
		}
		if(mOrderState == ATTACK)
		{
			mAttackMarker->Draw(buffer, camera);
		}
	}
}

void UnitObject::UpdateOrderState(float dt, Level *level)
{
	float diffX = 0.0f;
	float diffY = 0.0f;

	switch(mOrderState)
	{
	case NO_ORDER:
		mFrame = 0;
		mMarker->SetShow(false);
		mAttackMarker->SetShow(false);
		mAttackMarker->SetFrame(0);
		break;
	case MOVE:

			//if(!mPathFinder.GetTargetFound())
			//{
			//	mPathFinder.FindTarget(mTargetX, mTargetY, level);
			//	mPathFinder.MoveToNextNode(mScreenPosition, mMoveTargetX, mMoveTargetY, level);
			//}

			if(mFrame > 2)
			{
				mFrame = 0;
			}

			mMarker->SetShow(true);
			mMarker->SetFrame(3);
			mMarker->SetPosX(mTargetX);
			mMarker->SetPosY(mTargetY);

		if(!mCollision)
		{
			//for pathfinding
			//diffX = mMoveTargetX - mPosX;
			//diffY = mMoveTargetY - mPosY;
			diffX = mTargetX - mPosX;
			diffY = mTargetY - mPosY;

			diffX /= MagnitudeOf(diffX, diffY);
			diffY /= MagnitudeOf(diffX, diffY);

			mAccX = diffX * mSpeed;
			mAccY = diffY * mSpeed;
		}

		if(InBoundsOf(mPosX, mTargetX, 5.0f) && (InBoundsOf(mPosY, mTargetY, 5.0f)))
		{
			//Reset the pathfinder and orderstate
			//mPathFinder.Reset();
			mOrderState = NO_ORDER;
		}
		//else if(InBoundsOf(mPosX, mMoveTargetX , 32.0f) && (InBoundsOf(mPosY, mMoveTargetY, 32.0f)))
		//{
		//	//set the next node from the pathfinding
		//	mPathFinder.MoveToNextNode(mScreenPosition, mMoveTargetX, mMoveTargetY, level);
		//}

		CycleFrames(0, 2, 100);

		break;

	case ATTACK:

		mTargetX = mTargetObject->GetPosX();
		mMarker->SetShow(true);
		mMarker->SetFrame(1);
		mMarker->SetPosX(mTargetObject->GetPosX());
		mMarker->SetPosY(mTargetObject->GetPosY());

			if(InBoundsOf(mPosX,  mTargetObject->GetPosX(), mRange) &&
				(InBoundsOf(mPosY, mTargetObject->GetPosY(), mRange)))
			{
				if(!mPassive)
				{
					if((mFrame < 2) || (mFrame > 4))
					{
						mFrame = 2;
					}

					mAttackMarker->SetShow(true);
					mAttackMarker->Update(dt, mTargetObject->GetPosX(), mTargetObject->GetPosY());

					if(!mTimer.GetStarted())
					{
						mTimer.Start();
					}

					if(mTimer.GetTicks() >= mAttackSpeed)
					{
						mTargetObject->SetHealth(mDamage);
					}

					if(mTargetObject->GetDead())
					{
						mOrderState = NO_ORDER;
					}

					CycleFrames(2, 4, 500);
				}
			}
			else
			{
				//Reset frames of both sprite and attack marker
				mAttackMarker->SetFrame(0);
				if(mFrame > 2)
				{
					mFrame = 0;
				}

				if(!mCollision)
				{
					//Move the sprite towards the target
					diffX = mTargetObject->GetPosX() - mPosX;
					diffY = mTargetObject->GetPosY() - mPosY;

					diffX /= MagnitudeOf(diffX, diffY);
					diffY /= MagnitudeOf(diffX, diffY);

					mAccX = diffX * mSpeed;
					mAccY = diffY * mSpeed;
				}

				//Cycle through movement frames
				CycleFrames(0, 2, 100);
			}
		break;
	case GRAB:
		break;
	};

}

void UnitObject::SetSelected(bool _selected)
{
	mSelected = _selected;
}
void UnitObject::SetOrderState(int _orderState)
{
	mOrderState = _orderState;
}
void UnitObject::SetTargetObject(UnitObject *_target)
{
	mTargetObject = _target;
}
void UnitObject::SetTargetX(float _targetX)
{
	mTargetX = _targetX;
}
void UnitObject::SetTargetY(float _targetY)
{
	mTargetY = _targetY;
}
void UnitObject::SetHealth( float _healthDamage)
{
	mHealth -= _healthDamage;
}
void UnitObject::SetDead( bool _dead)
{
	mDead = _dead;
}
void UnitObject::SetMoveTargetX( float _moveTargetX)
{
	mMoveTargetX = _moveTargetX;
}
void UnitObject::SetMoveTargetY( float _moveTargetY)
{
	mMoveTargetY = _moveTargetY;
}

bool UnitObject::GetSelected()
{
	return mSelected;
}
float UnitObject::GetTargetX()
{
	return mTargetX;
}
float UnitObject::GetTargetY()
{
	return mTargetY;
}
int UnitObject::GetOrderState()
{
	return mOrderState;
}
float UnitObject::GetRange()
{
	return mRange;
}
float UnitObject::GetHealth()
{
	return mHealth;
}
float UnitObject::GetDamage()
{
	return mDamage;
}
float UnitObject::GetAttackSpeed()
{
	return mAttackSpeed;
}
bool UnitObject::GetDead()
{
	return mDead;
}