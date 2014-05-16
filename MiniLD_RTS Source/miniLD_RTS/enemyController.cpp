#include "EnemyController.h"

EnemyController::EnemyController(bool _playAs) : mNewUnit(NULL), mPlayAsMarines(_playAs)
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Initalise(SDL_Surface* marineSprite, SDL_Surface* alienSprite,
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

	for(unsigned int t = 0; t < level->GetFloorTileAmount(); t++)
	{
		if(level->GetFloorTile(t)->GetTileType() == 9)
		{
			spawnCounter += 1;
			spawnTiles.push_back(t);
		}
	}

	spawnDone = spawnCounter;

	while(spawnDone > 0)
	{
		for(currUnit = lastUnit; currUnit < mEnemyUnits.size() / spawnCounter + lastUnit; currUnit++)
		{
			mEnemyUnits[currUnit]->SetPosX(level->GetFloorTile(spawnTiles[currTile])->GetPosX() + rand() % 32);
			mEnemyUnits[currUnit]->SetPosY(level->GetFloorTile(spawnTiles[currTile])->GetPosY() + rand() % 32);
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
		spawnDone -=1;
	}
}

void EnemyController::Update( float dt , PlayerController *player , Camera *camera, Level *level )
{

	//Stop from clumping
	for(unsigned int i = 0; i < mEnemyUnits.size(); i++)
	{
		for(unsigned int j = 0; j < mEnemyUnits.size(); j++)
		{
			if(j != i)
			{
				if(CheckCollision(mEnemyUnits[i]->GetCollisionBox(), mEnemyUnits[j]->GetCollisionBox()) && 
					(!mEnemyUnits[i]->GetDead()) && (!mEnemyUnits[j]->GetDead()))
				{
					float diffX = mEnemyUnits[j]->GetPosX() - mEnemyUnits[i]->GetPosX();
					float diffY = mEnemyUnits[j]->GetPosY() - mEnemyUnits[i]->GetPosY();

					diffX /= MagnitudeOf(diffX, diffY);
					diffY /= MagnitudeOf(diffX, diffY);

					mEnemyUnits[j]->SetAccX(diffX * (mEnemyUnits[j]->GetSpeed() / 5));
					mEnemyUnits[j]->SetAccY(diffY * (mEnemyUnits[j]->GetSpeed() / 5));
				}
			}
		}
	}

	//Attacks the closest unit if within range
	for(unsigned int i = 0; i < mEnemyUnits.size(); i++)
	{
		if(!mEnemyUnits[i]->GetDead())
		{
			for(unsigned int j = 0; j < player->GetUnitAmount(); j++)
			{
				if(InBoundsOf(mEnemyUnits[i]->GetPosX(), player->GetUnit(j)->GetPosX(), 100.0f) &&
					(InBoundsOf(mEnemyUnits[i]->GetPosY(), player->GetUnit(j)->GetPosY(), 100.0f)) &&
					(!player->GetUnit(j)->GetDead()))
				{
					mEnemyUnits[i]->SetOrderState(2);
					mEnemyUnits[i]->SetTargetX(player->GetUnit(j)->GetCollisionBox().x + camera->GetCamera().x);
					mEnemyUnits[i]->SetTargetY(player->GetUnit(j)->GetCollisionBox().y + camera->GetCamera().y);
					mEnemyUnits[i]->SetTargetObject(player->GetUnit(j));
				}
			}
		}
	}

	for(unsigned int i = 0; i < mEnemyUnits.size(); i++)
	{
		mEnemyUnits[i]->Update(dt, level);
	}
}

void EnemyController::Draw( SDL_Surface* buffer, Camera *camera)
{
	for(unsigned int i = 0; i < mEnemyUnits.size(); i++)
	{
		mEnemyUnits[i]->Draw( buffer, camera );
	}
}

UnitObject* EnemyController::GetUnit( int _unit)
{
	if(_unit > mEnemyUnits.size())
	{
		return NULL;
	}

	return mEnemyUnits[_unit];
}

int EnemyController::GetUnitAmount()
{
	return mEnemyUnits.size();
}

void EnemyController::InitMarines(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar)
{
		//Marines
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new MarineObject(marineSprite, markers, healthBar, rand() % 640, rand() % 480);

		mEnemyUnits.push_back(mNewUnit);
	}

	//MachineGunners
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new MachineGunnerObject(marineSprite, markers, healthBar, rand() % 640, rand() % 480);

		mEnemyUnits.push_back(mNewUnit);
	}

	//Medic
	for(unsigned int i = 0; i < 5; i++)
	{

	}
}

void EnemyController::InitAliens(SDL_Surface* alienSprite, SDL_Surface* markers, SDL_Surface* healthBar)
{
	//Slicer
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new SlicerObject(alienSprite, markers, healthBar, rand() % 640, rand() % 480);

		mEnemyUnits.push_back(mNewUnit);
	}

	//Spitter
	for(unsigned int i = 0; i < 5; i++)
	{
		mNewUnit = NULL;
		mNewUnit = new SpitterObject(alienSprite, markers, healthBar, rand() % 640, rand() % 480);

		mEnemyUnits.push_back(mNewUnit);
	}

	//HeadBug
	for(unsigned int i = 0; i < 5; i++)
	{

	}
}