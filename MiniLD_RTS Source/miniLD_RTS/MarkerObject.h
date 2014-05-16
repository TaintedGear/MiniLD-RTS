#ifndef MARKEROBJECT_H
#define MARKEROBJECT_H

#include "GameObject.h"
#include "Camera.h"

class MarkerObject : public GameObject
{
public:
	explicit MarkerObject(SDL_Surface *sprite, float posX, float posY, int _offset) : GameObject
		(sprite, posX, posY)
	{
		mSheetWidth = 32;
		mSheetHeight = 32;
		mSheetY = _offset;

		mScreenWidth = 32;
		mScreenHeight = 32;

		mOffset = _offset;
		mCycle = false;
	}
	explicit MarkerObject() : GameObject()
	{
	}
	~MarkerObject();

	void Update(float dt, float targetPosX, float targetPosY);
	void Draw(SDL_Surface *buffer, Camera *camera);

	void SetCycle(bool _cycle);
	void SetOffset(int _offset);
private:

	int mOffset;
	bool mCycle;
};

#endif