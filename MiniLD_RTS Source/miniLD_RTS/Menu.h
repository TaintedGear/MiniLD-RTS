#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "Mouse.h"
#include "MainMenu.h"

class Menu
{
public:
	Menu(SDL_Surface* _background);
	~Menu();

	void Update( int _menuState, Mouse *mouse);
	void Draw(SDL_Surface* buffer);

private:

	int mState;
	enum mStates {MAIN_MENU, GAME_SELECTION, OPTIONS, PAUSED, GAME_OVER};

	MainMenu *mMainMenu;
};

#endif