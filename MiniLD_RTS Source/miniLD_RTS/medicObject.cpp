#include "MedicObject.h"

MedicObject::~MedicObject()
{
}

void MedicObject::Update( float dt, Level *level)
{
	UnitObject::Update(dt, level);
}

void MedicObject::Draw(SDL_Surface* buffer, Camera *camera)
{
	UnitObject::Draw(buffer, camera);
}
