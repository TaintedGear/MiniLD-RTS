#include "MainMenu.h"

MainMenu::MainMenu(SDL_Surface *_background) : mTitle(NULL)
{
	mFontColor.r = 0.0f;
	mFontColor.b = 0.0f;
	mFontColor.g = 0.0f;

	mTitleRect.y = 480/2;
	mTitleRect.x = 640/2;

	mBackground = _background;
	CheckSurfaceNull(mBackground);

	mFont = TTF_OpenFont("Fonts/hyperion.ttf", 30);
}

MainMenu::~MainMenu()
{

}

void MainMenu::Update(Mouse *mouse)
{
}

void MainMenu::Draw(SDL_Surface* buffer)
{
	SDL_BlitSurface(mBackground, NULL, buffer, NULL);
	
	if(mTitle = TTF_RenderText_Solid(mFont, "miniLD RTS", mFontColor))
	{
		SDL_BlitSurface(mTitle, NULL, buffer, &mTitleRect);
		FreeSurface(mTitle);
	}

}
