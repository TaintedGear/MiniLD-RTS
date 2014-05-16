#include "MachineGunnerObject.h"

MachineGunnerObject::~MachineGunnerObject()
{

}

void MachineGunnerObject::Update( float dt, Level *level )
{
	UnitObject::Update( dt, level );
}

void MachineGunnerObject::Draw(SDL_Surface* buffer, Camera *camera)
{

	UnitObject::Draw(buffer, camera);
}