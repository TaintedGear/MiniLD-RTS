#include "MarineObject.h"

MarineObject::~MarineObject()
{
}

void MarineObject::Update(float dt, Level *level)
{
	UnitObject::Update(dt, level);
}

void MarineObject::Draw(SDL_Surface *buffer, Camera *camera)
{
	UnitObject::Draw(buffer, camera);
}