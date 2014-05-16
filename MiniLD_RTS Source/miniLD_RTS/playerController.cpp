#include "PlayerController.h"

PlayerController::PlayerController(bool _playAs) : mNewUnit(NULL), mPlayAsMarines(_playAs)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Initalise(SDL_Surface* marineSprite, SDL_Surface* alienSprite,
	SDL_Surface* markers, SDL_Surface* healthBar, Level *level)
{
	vector<int> spawnTiles;
	int spawnCounter = 0;
	int currTile = 0;
	int currUnit = 0;
	int lastUnit = 0;
	int spawnDone = 0;

	if(mPlayAsMarines)
	{
		InitMarines(marineSprite, markers, healthBar);
	}
	else
	{
		InitAliens(alienSprite, markers, healthBar);
	}

	//Spawns all the units on the correct tiles (must have less tiles then the amount of units
	for(unsigned int t = 0; t < level->GetFloorTileAmount(); t++)
	{
		if(level->GetFloorTile(t)->GetTileType() == 8)
		{
			spawnCounter += 1;
			spawnTiles.push_back(t);
		}
	}

	spawnDone = spawnCounter;

	while(spawnDone > 0)
	{
		for(currUnit = lastUnit; currUnit < mPlayerUnits.size() / spawnCounter + lastUnit; currUnit++)
		{
			mPlayerUnits[currUnit]->SetPosX(level->GetFloorTile(spawnTiles[currTile])->GetPosX() + rand() % 32);
			mPlayerUnits[currUnit]->SetPosY(level->GetFloorTile(spawnTiles[currTile])->GetPosY() + rand() % 32);
		}
		if(currTile > spawnTiles.size())
		{
			currTile = 0;
		}
		else
		{
			currTile += 1;
		}

		lastUnit = currUnit;
		spawnDone -= 1;
	}
}

void PlayerController::Update( float dt, EnemyController *enemy, Level *currLevel, Camera *camera )
{

	float tempPosX = 0.0f;
	float tempPosY = 0.0f;

	//CheckCollision from wall tiles
	//for(unsigned int i = 0; i < mPlayerUnits.size(); i++)
	//{
	//	if(!mPlayerUnits[i]->GetCollision())
	//	{
	//		tempPosX = mPlayerUnits[i]->GetPosX();
	//		tempPosY = mPlayerUnits[i]->GetPosY();
	//	}

	//	for(unsigned int j = 0; j < currLevel->GetWallTileAmount(); j++)
	//	{
	//		if(CheckCollision(mPlayerUnits[i]->GetCollisionBox(), currLevel->GetWallTile(j)->GetCollisionBox()))
	//		{
	//			//mPlayerUnits[i]->SetPosX(tempPosX);
	//			//mPlayerUnits[i]->SetPosY(tempPosY);
	//			mPlayerUnits[i]->SetVelX(mPlayerUnits[i]->GetVelX() * -1);
	//			mPlayerUnits[i]->SetVelY(mPlayerUnits[i]->GetVelY() * -1);

	//			mPlayerUnits[i]->SetCollision(true);
	//		}
	//		else
	//		{
	//			mPlayerUnits[i]->SetCollision(false);
	//		}
	//	}
	//}

	//Stop from clumping
	for(unsigned int i = 0; i < mPlayerUnits.size(); i++)
	{
		for(unsigned int j = 0; j < mPlayerUnits.size(); j++)
		{
			if(j != i)
			{
				if(CheckCollision(mPlayerUnits[i]->GetCollisionBox(), mPlayerUnits[j]->GetCollisionBox()) && 
					(!mPlayerUnits[i]->GetDead()) && (!mPlayerUnits[j]->GetDead()))
				{
					float diffX = mPlayerUnits[j]->GetPosX() - mPlayerUnits[i]->GetPosX();
					float diffY = mPlayerUnits[j]->GetPosY() - mPlayerUnits[i]->GetPosY();

					diffX /= MagnitudeOf(diffX, diffY);
					diffY /= MagnitudeOf(diffX, diffY);

					mPlayerUnits[j]->SetAccX(diffX * (mPlayerUnits[j]->GetSpeed() / 5));
					mPlayerUnits[j]->SetAccY(diffY * (mPlayerUnits[j]->GetSpeed() / 5));
				}
			}
		}
	}

	//Attacks the closest unit if within range
	for(unsigned int i = 0; i < mPlayerUnits.size(); i++)
	{
		if(mPlayerUnits[i]->GetOrderState() == 0)
		{
			for(unsigned int j = 0; j < enemy->GetUnitAmount(); j++)
			{
				if(InBoundsOf(mPlayerUnits[i]->GetPosX(), enemy->GetUnit(j)->GetPosX(), 100.0f) &&
					(InBoundsOf(mPlayerUnits[i]->GetPosY(), enemy->GetUnit(j)->GetPosY(), 100.0f)) &&
					(!enemy->GetUnit(j)->GetDead()))
				{
					mPlayerUnits[i]->SetOrderState(2);
					mPlayerUnits[i]->SetTargetX(enemy->GetUnit(j)->GetCollisionBox().x + camera->GetCamera().x);
					mPlayerUnits[i]->SetTargetY(enemy->GetUnit(j)->GetCollisionBox().y + camera->GetCamera().y);
					mPlayerUnits[i]->SetTargetObject(enemy->GetUnit(j));
				}
			}
		}
	}

	for(unsigned int i = 0; i < mPlayerUnits.size(); i++)
	{
		mPlayerUnits[i]->Update(dt, currLevel);
	}
}

void PlayerController::Draw( SDL_Surface* buffer, Camera *camera)
{
	for(unsigned int i = 0; i < mPlayerUnits.size(); i++)
	{
		mPlayerUnits[i]->Draw( buffer, camera );
		//SDL_FillRect(buffer, &mPlayerUnits[i]->GetCollisionBox(), SDL_MapRGB(buffer->format, 0xFF, 0xFF, 0xFF));
	}
}

UnitObject* PlayerController::GetUnit( int _unit)
{
	if(_unit > mPlayerUnits.size())
	{
		return NULL;
	}

	return mPlayerUnits[_unit];
}

int PlayerController::GetUnitAmount()
{
	return mPlayerUnits.size();
}

void PlayerController::InitMarines(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar)
{
	//Marines
	for(unsigned int i = 0; i < 10; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new MarineObject(marineSprite, markers, healthBar, rand() % 640, rand() % 480);

		mPlayerUnits.push_back(mNewUnit);
	}

	//MachineGunners
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new MachineGunnerObject(marineSprite, markers, healthBar, rand() % 640, rand() % 480);

		mPlayerUnits.push_back(mNewUnit);
	}

	//Medic
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new MedicObject(marineSprite, markers, healthBar, rand() % 640, rand() % 480);

		mPlayerUnits.push_back(mNewUnit);
	}
}

void PlayerController::InitAliens(SDL_Surface* alienSprite, SDL_Surface* markers, SDL_Surface* healthBar)
{
	//Slicer
	for(unsigned int i = 0; i < 10; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new SlicerObject(alienSprite, markers, healthBar, rand() % 640, rand() % 480);

		mPlayerUnits.push_back(mNewUnit);
	}

	//Spitter
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new SpitterObject(alienSprite, markers, healthBar, rand() % 640, rand() % 480);

		mPlayerUnits.push_back(mNewUnit);
	}

	//HeadBug
	for(unsigned int i = 0; i < 5; i++)
	{

	}
}