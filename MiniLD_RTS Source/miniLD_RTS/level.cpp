#include "Level.h"

Level::Level(string floorFile, string wallFile, SDL_Surface* tileSheet, int _levelWidth, int _levelHeight) 
	: mFloorFile(floorFile), mWallFile(wallFile), mLevelWidth(_levelWidth), mLevelHeight(_levelHeight), mLevelLoaded(false),
	mTileSheet(tileSheet)
{
	LoadLevel();
}

Level::~Level()
{
	delete mTileMap;
}

void Level::Update( float dt )
{
	for(int i = 0; i < mFloorTiles.size(); i++)
	{
		mFloorTiles[i]->Update( dt );
	}
	for(int i = 0; i < mWallTiles.size(); i++)
	{
		mWallTiles[i]->Update( dt );
	}
}

void Level::Draw( SDL_Surface* buffer, Camera *camera)
{
	for(int i = 0; i < mFloorTiles.size(); i++)
	{
		mFloorTiles[i]->Draw(buffer, camera);
	}
	for(int i = 0; i < mWallTiles.size(); i ++)
	{
		mWallTiles[i]->Draw(buffer, camera);
		//SDL_FillRect( buffer, &mWallTiles[i]->GetCollisionBox(), SDL_MapRGB(buffer->format, 100, 100, 20));
	}
}

void Level::LoadLevel()
{
	int total = mLevelWidth * mLevelHeight;
	mTileMap = new int[total];

	if(!LoadFloorLevel())
	{
		//error
	}
	if(!LoadWallLevel())
	{
		//error
	}
}

bool Level::LoadFloorLevel()
{
	FILE *file;

	file = fopen(mFloorFile.c_str(), "rb");

	if(file != NULL)
	{
		for(int y = 0; y < mLevelHeight; y++)
		{
			for(int x = 0; x < mLevelWidth; x++)
			{
				fscanf(file, "%d", &mTileMap[mLevelWidth * x + y]);
			}
		}

		mLevelLoaded = true;
	}

	if(mLevelLoaded)
	{
		int i = 0;
		for(int y = 0; y < mLevelHeight; y++)
		{
			for(int x = 0; x < mLevelWidth; x++)
			{
				if(mTileMap[mLevelWidth * x + y] != 0)
				{
					mNewTile = NULL;
					mNewTile = new TileObject(mTileSheet,(int)x * 32, (int)y * 32, mTileMap[mLevelWidth * x + y], false, i);

					mFloorTiles.push_back(mNewTile);
				}

				i++;
			}

			i++;
		}
	}

	fclose(file);
	return true;
}
bool Level::LoadWallLevel()
{
	FILE *file;

	file = fopen(mWallFile.c_str(), "rb");

	
	if(file != NULL)
	{
		for(int y = 0; y < mLevelHeight; y++)
		{
			for(int x = 0; x < mLevelWidth; x++)
			{
				fscanf(file, "%d", &mTileMap[mLevelWidth * x + y]);
			}
		}

		mLevelLoaded = true;
	}

	if(mLevelLoaded)
	{
		int i = 0;
		for(int y = 0; y < mLevelHeight; y++)
		{
			for(int x = 0; x < mLevelWidth; x++)
			{
				if(mTileMap[mLevelWidth * x + y] != 0)
				{
					mNewTile = NULL;
					mNewTile = new TileObject(mTileSheet, (int)x * 32, (int)y * 32, mTileMap[mLevelWidth * x + y], false, x+y);

					mWallTiles.push_back(mNewTile);
				}

				i++;
			}

			i++;
		}
	}

	fclose(file);
	return true;
}

TileObject* Level::GetWallTile(int _tile)
{
	if(_tile <= mWallTiles.size())
	{
		return mWallTiles[_tile];
	}
	else
	{
		return NULL;
	}
}
TileObject* Level::GetFloorTile(int _tile)
{
	if(_tile < mFloorTiles.size())
	{
		return mFloorTiles[_tile];
	}
	else
	{
		return NULL;
	}
}
int Level::GetWallTileAmount()
{
	return mWallTiles.size();
}
int Level::GetFloorTileAmount()
{
	return mFloorTiles.size();
}
int Level::GetLevelWidth()
{
	return mLevelWidth;
}
int Level::GetLevelHeight()
{
	return mLevelHeight;
}