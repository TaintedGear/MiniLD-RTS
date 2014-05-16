#include "TileObject.h"

TileObject::TileObject(SDL_Surface* tileSheet, float _posX, float _posY, int _tileType, bool blockable, int tileId) 
	: mTile(tileSheet), mPosX(_posX), mPosY(_posY), mTileWidth(32), mTileHeight(32),
	mScreenHeight(0.0f), mScreenWidth(0.0f), mBlockable(blockable), mWaypoint(false), mSheetX(0), mSheetY(0),
	mTileType(_tileType), mTileId(tileId)
{
	Uint32 colourKey = SDL_MapRGB(mTile->format, 0xFF, 0, 0xFF);
	SDL_SetColorKey(mTile, SDL_SRCCOLORKEY | SDL_RLEACCEL, colourKey);
}

TileObject::~TileObject()
{
	if(CheckSurfaceNull(mTile))
	{
		SDL_FreeSurface(mTile);
	}
}

void TileObject::Update( float dt )
{

	mScreenPosition.x = mPosX;
	mScreenPosition.y = mPosY;
	mScreenPosition.h = mTileHeight;
	mScreenPosition.w = mTileWidth;

	mTileSize.x = mSheetX;
	mTileSize.y = mSheetY;
	mTileSize.h = mTileHeight;
	mTileSize.w = mTileWidth;

}

void TileObject::Draw( SDL_Surface *buffer, Camera *camera)
{

	switch(mTileType)
	{
	case TOP_WALL:
		mSheetY = 0;
		break;
	case BOTTOM_WALL:
		mSheetY = 32;
		break;
	case WALL:
		mSheetY = 126;
		break;
	case FLOOR:
		mSheetY = 126;
		mSheetX = 32;
		break;
	case TOP_WALL_FLIPPED:
		mSheetY = 64;
		break;
	case BOTTOM_WALL_FLIPPED:
		mSheetY = 92;
		break;
	case PLAYER_SPAWN_TILE:
		mSheetY = 126;
	case ENEMY_SPAWN_TILE:
		mSheetY = 126;
		break;
	}

	mScreenPosition.x = mPosX - camera->GetPosX();
	mScreenPosition.y = mPosY - camera->GetPosY();
	mCollisionBox = mScreenPosition;

	SDL_BlitSurface(mTile, &mTileSize, buffer, &mScreenPosition);
}

SDL_Rect TileObject::GetCollisionBox()
{
	return mCollisionBox;
}
float TileObject::GetPosX()
{
	return mPosX;
}
float TileObject::GetPosY()
{
	return mPosY;
}
int TileObject::GetTileType()
{
	return mTileType;
}
int TileObject::GetTileId()
{
	return mTileId;
}