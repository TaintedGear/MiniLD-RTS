#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Camera.h"
#include "TileObject.h"

using std::string;
using std::vector;

class Level
{
public:
	Level(string floorfile, string wallFile, SDL_Surface* tileSheet, int _levelWidth, int _levelHeight);
	~Level();

	void Update( float dt );
	void Draw(SDL_Surface *buffer, Camera *camera);

	TileObject* GetWallTile(int _tile);
	TileObject* GetFloorTile(int _tile);
	int GetWallTileAmount();
	int GetFloorTileAmount();
	int GetLevelWidth();
	int GetLevelHeight();

private:

	int *mTileMap;

	void LoadLevel();
	bool LoadFloorLevel();
	bool LoadWallLevel();

	TileObject *mNewTile;

	bool mLevelLoaded;
	string mFloorFile,
		mWallFile;
	int mLevelWidth,
		mLevelHeight;
	SDL_Surface* mTileSheet;

	vector<TileObject *> mFloorTiles;
	vector<TileObject *> mWallTiles;
};


#endif