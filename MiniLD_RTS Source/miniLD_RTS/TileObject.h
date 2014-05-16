#ifndef TILE_OBJECT_H
#define TILE_OBJECT_H

#include "SDL.h"
#include "Utillitys.h"
#include "Camera.h"

using namespace Utillitys;

class TileObject
{
public:
	TileObject(SDL_Surface *tileSheet, float _posX, float _posY, int _tileType, 
		bool blockable, int tileId);
	~TileObject();

	virtual void Update( float dt );
	virtual void Draw( SDL_Surface* buffer, Camera *camera);

	int GetTileId();
	int GetTileType();
	float GetPosX();
	float GetPosY();
	SDL_Rect GetCollisionBox();
private:

	bool mBlockable,
		mWaypoint;

	float mPosX,
		mPosY;

	int	mTileWidth,
		mTileHeight,
		mSheetX,
		mSheetY,
		mScreenHeight,
		mScreenWidth,
		mTileType,
		mTileId;

	SDL_Surface *mTile;

	SDL_Rect mScreenPosition,
		mTileSize,
		mCollisionBox; // not sure about this

	enum mTileTypes { TOP_WALL = 1, BOTTOM_WALL = 2, WALL = 3, FLOOR = 5 ,
	TOP_WALL_FLIPPED = 6, BOTTOM_WALL_FLIPPED = 7, PLAYER_SPAWN_TILE = 8,
	ENEMY_SPAWN_TILE = 9};
};

#endif