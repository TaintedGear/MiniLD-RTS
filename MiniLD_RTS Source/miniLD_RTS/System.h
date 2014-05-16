#ifndef SYSTEM_H
#define SYSTEM_H

#include "SDL.h"
#include "SDL_ttf.h"

class System
{
public:
	System();
	~System();

	bool Initalise();
	bool Done();
	void Shutdown();

	SDL_Surface* GetBuffer();
	SDL_Event& GetEvent();

	int GetScreenWidth();
	int GetScreenHeight();
private:

	bool mShutdown,
		mFullscreen;

	int mWidth,
		mHeight,
		mBpp,
		mFps;

	SDL_Event event;
	SDL_Surface *mBuffer;
};


#endif