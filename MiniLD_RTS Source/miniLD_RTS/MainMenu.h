#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "Utillitys.h"

#include "Mouse.h"

using namespace Utillitys;

class MainMenu
{
public:
	MainMenu(SDL_Surface *_background);
	~MainMenu();

	void Update(Mouse *mouse);
	void Draw(SDL_Surface* buffer);
private:

	SDL_Color mFontColor;

	TTF_Font *mFont;

	SDL_Surface *mBackground;
	SDL_Surface *mTitle;

	SDL_Rect mPlayButton; // temp
	SDL_Rect mTitleRect;
};

#endif