#include "System.h"


System::System() : mHeight(800), mWidth(1280), mBpp(32), mFps(60),
	mFullscreen(false), mShutdown(false), mBuffer(NULL) 
{
}

System::~System()
{
	if(!mShutdown)
	{
		Shutdown();
	}
}

bool System::Initalise()
{
	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return false;
	}
	if(TTF_Init() == -1)
	{
		return false;
	}

	if(mFullscreen)
	{
		mBuffer = SDL_SetVideoMode(mWidth, mHeight, mBpp, SDL_SWSURFACE | SDL_FULLSCREEN);
	}
	else
	{
		mBuffer = SDL_SetVideoMode(mWidth, mHeight, mBpp, SDL_SWSURFACE);
	}

	if(mBuffer == NULL)
	{
		return false;
	}

	SDL_WM_SetCaption("MiniLD RTS", NULL);
	
	return true;
}

bool System::Done()
{
	SDL_PollEvent(&event);

	if( event.type == SDL_QUIT )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void System::Shutdown()
{
	mShutdown = true;

	SDL_FreeSurface(mBuffer);

	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* System::GetBuffer()
{
	return mBuffer;
}

SDL_Event& System::GetEvent()
{
	return event;
}

int System::GetScreenWidth()
{
	return mWidth;
}

int System::GetScreenHeight()
{
	return mHeight;
}