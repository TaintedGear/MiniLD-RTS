#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Utillitys.h"
#include "Level.h"
#include "Camera.h"
#include "PlayerController.h"
#include "UnitObject.h"

#include "MarineObject.h"
#include "MachineGunnerObject.h"

#include "SlicerObject.h"
#include "SpitterObject.h"


using std::vector;
using namespace Utillitys;

class PlayerController;

class EnemyController
{
public:
	EnemyController(bool _playAs);
	~EnemyController();

	void Initalise(SDL_Surface* marineSprite, SDL_Surface* alienSprite,
		SDL_Surface* markers, SDL_Surface* healthBar, Level *level);
	void Update( float dt, PlayerController *player , Camera *camera, Level *level );
	void Draw( SDL_Surface* buffer, Camera *camera );

	UnitObject* GetUnit(int _unit);
	int GetUnitAmount();

private:

	void InitMarines(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar);
	void InitAliens(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar);

	bool mPlayAsMarines;
	UnitObject* mNewUnit;
	vector<UnitObject*> mEnemyUnits;
};

#endif