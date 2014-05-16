#include "Menu.h"

Menu::Menu(SDL_Surface* _background) : mState(0)
{
	mMainMenu = new MainMenu(_background);
}

Menu::~Menu()
{
	delete mMainMenu;
}

void Menu::Update( int _menuState, Mouse *mouse)
{
	mState = _menuState;

	switch(mState)
	{
	case MAIN_MENU:
		mMainMenu->Update(mouse);
		break;
	case GAME_SELECTION:
		break;
	case OPTIONS:
		break;
	case PAUSED:
		break;
	case GAME_OVER:
		break;
	}
}


void Menu::Draw(SDL_Surface* buffer)
{
	switch(mState)
	{
	case MAIN_MENU:
		mMainMenu->Draw(buffer);
		break;
	case GAME_SELECTION:
		break;
	case OPTIONS:
		break;
	case PAUSED:
		break;
	case GAME_OVER:
		break;
	}
}
