#include "SpitterObject.h"

SpitterObject::~SpitterObject()
{
}

void SpitterObject::Update( float dt, Level *level )
{
	UnitObject::Update(dt, level);
}

void SpitterObject::Draw( SDL_Surface* buffer, Camera *camera)
{
	UnitObject::Draw(buffer, camera);
}