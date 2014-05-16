#ifndef UTILLITYS_H
#define UTILLITYS_H

#include <iostream>
#include <math.h>
#include "SDL.h"

namespace Utillitys
{
	inline float NormalizeX(float vecX, float vecY)
	{
		float mag = (float)sqrtf(vecX * vecX + vecY * vecY);
		return vecX /= mag;
	}
	inline float NormalizeY(float vecX, float vecY)
	{
		float mag = (float)sqrtf(vecX * vecX + vecY * vecY);
		return vecX /= mag;
	}
	inline float MagnitudeOf(float vecX, float vecY)
	{
		return (float)sqrtf((vecX * vecX) + (vecY * vecY));
	}

	inline bool CheckCollision(SDL_Rect a, SDL_Rect b)
	{
		float leftA = (float)a.x,
			rightA = (float)a.x + a.w,
			topA = (float)a.y,
			bottomA = (float)a.y + a.h;

		float leftB = (float)b.x,
			rightB = (float)b.x + b.w,
			topB = (float)b.y,
			bottomB = (float)b.y + b.h;

		if(bottomA <= topB)
		{
			return false;
		}
		if(topA >= bottomB)
		{
			return false;
		}
		if(rightA <= leftB)
		{
			return false;
		}
		if(leftA >= rightB)
		{
			return false;
		}

		return true;
	}

	inline float PercentageOf(float number, float percentage)
	{
		float result = (number * percentage) / 100;

		return result;
	}

	inline bool CheckSurfaceNull(SDL_Surface *surface)
	{
		if(surface == NULL)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	inline bool InBoundsOf( float number, float target, float area )
	{
		if((number <= target + area) && (number >= target - area))
		{
			return true;
		}
		return false;
	}
	inline void FreeSurface(SDL_Surface *surface)
	{
		if(surface == NULL) SDL_FreeSurface(surface);
	}
	inline bool CheckFlipped(float pos, float target)
	{
		if(pos > target)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

#endif