#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Utillitys.h"
#include "Camera.h"
#include "Level.h"
#include "EnemyController.h"
#include "UnitObject.h"

#include "MarineObject.h"
#include "MachineGunnerObject.h"
#include "MedicObject.h"

#include "SlicerObject.h"
#include "SpitterObject.h"


using std::vector;
using namespace Utillitys;
class EnemyController;

class PlayerController
{
public:
	PlayerController(bool _playAs);
	~PlayerController();

	void Initalise(SDL_Surface* marineSprite, SDL_Surface* alienSprite, 
		SDL_Surface* markers, SDL_Surface* healthBar, Level *level);
	void Update( float dt, EnemyController *enemy, Level *currLevel, Camera *camera );
	void Draw( SDL_Surface* buffer, Camera *camera );

	UnitObject* GetUnit(int _unit);
	int GetUnitAmount();

private:

	void InitMarines(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar);
	void InitAliens(SDL_Surface* marineSprite, SDL_Surface* markers, SDL_Surface* healthBar);

	bool mPlayAsMarines;
	UnitObject* mNewUnit;
	vector<UnitObject*> mPlayerUnits;
};

#endif