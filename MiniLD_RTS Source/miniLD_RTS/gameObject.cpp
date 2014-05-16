#include "GameObject.h"

GameObject::GameObject(SDL_Surface* _sprite, float _posX, float _posY) :
mSprite(_sprite), mSheetWidth(0), mSheetHeight(0), mScreenHeight(0), 
	mScreenWidth(0), mState(0), mFrame(0), mPosX(_posX), mPosY(_posY),
	mShow(false), mFlipped(false), mSheetY(0), mCollision (false)
{
	//sets the magenta color key
	Uint32 colourKey = SDL_MapRGB(mSprite->format, 0xFF, 0, 0xFF);
	SDL_SetColorKey(mSprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colourKey);

	mCollisionBox.x = 0;
	mCollisionBox.y = 0;
	mCollisionBox.h = 0;
	mCollisionBox.w = 0;
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(SDL_Surface* _buffer, Camera *_camera)
{
	if(mShow)
	{
		mSpriteSize.h = mSheetHeight;
		mSpriteSize.w = mSheetWidth;
		mSpriteSize.x = mFrame * mSheetWidth;
		mSpriteSize.y = mSheetY;

		if(mFlipped)
		{
			mSpriteSize.y = mSheetY + mSheetHeight;
		}

		mScreenPosition.x = mPosX - _camera->GetCamera().x;
		mScreenPosition.y = mPosY - _camera->GetCamera().y;
		mScreenPosition.w = mScreenWidth;
		mScreenPosition.h = mScreenHeight;

		mCollisionBox = mScreenPosition;

		SDL_BlitSurface(mSprite, &mSpriteSize, _buffer, &mScreenPosition);
	}
}

void GameObject::CycleFrames(int frameStart, int frameStop, int duration)
{

	if(!mTimer.GetStarted())
	{
		mTimer.Start();
	}

	if(mFrame >= frameStop)
	{
		mFrame = frameStart;
	}

	if(mTimer.GetTicks() >= duration)
	{
		mFrame += 1;
		mTimer.Stop();
	}
}

SDL_Rect GameObject::GetCollisionBox()
{
	return mCollisionBox;
}
float GameObject::GetPosX()
{
	return mPosX;
}
float GameObject::GetPosY()
{
	return mPosY;
}
bool GameObject::GetCollision()
{
	return mCollision;
}

void GameObject::SetShow(bool _show)
{
	mShow = _show;
}
void GameObject::SetFrame(int _frame)
{
	mFrame = _frame;
}
void GameObject::SetPosX(float _posX)
{
	mPosX = _posX;
}
void GameObject::SetPosY(float _posY)
{
	mPosY = _posY;
}
void GameObject::SetCollision(bool _collision)
{
	mCollision = _collision;
}