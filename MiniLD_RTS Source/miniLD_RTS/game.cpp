#include "Game.h"

Game::Game() : mShutdown(false), mBuffer(NULL), mAlienSheet(NULL), mMarineSheet(NULL), 
	mThisTime(0.0f), mLastTime(0.0f), mState(0)
{
}

Game::~Game()
{
	if(!mShutdown)
	{
		Shutdown();
	}
}

bool Game::Initalise()
{
	//set up sdl
	if(!mSystem.Initalise())
	{
		return false;
	}

	//set up buffer
	mBuffer = mSystem.GetBuffer();

	if(mBuffer == NULL)
	{
		return false;
	}

	//load any images needed 
	mAlienSheet = LoadImage("Sprites/alien_sprites.bmp");
	mMarineSheet = LoadImage("Sprites/marine_sprites.bmp");
	mTempBackground = LoadImage("Sprites/BackGround.bmp");
	mMarkerSheet = LoadImage("Sprites/markers_sheet.bmp");
	mHealthSheet = LoadImage("Sprites/health_bar.bmp");
	mTileSheet = LoadImage("Sprites/tile_sheet_temp.bmp");

	CheckSurfaceNull(mAlienSheet);
	CheckSurfaceNull(mMarineSheet);
	CheckSurfaceNull(mTempBackground);
	CheckSurfaceNull(mMarkerSheet);
	CheckSurfaceNull(mHealthSheet);

	//load inital classes
	mLevelManager = new LevelManager(mTileSheet);
	mPlayer = new PlayerController(true);
	mEnemy = new EnemyController(false);
	mMenu = new Menu(mTempBackground);
	mCamera = new Camera(mSystem.GetScreenWidth(), mSystem.GetScreenHeight(), 0, 0);

	return true;
}

void Game::Run()
{
	Uint8* keys = SDL_GetKeyState(NULL);

	mPlayer->Initalise(mMarineSheet, mAlienSheet, mMarkerSheet, mHealthSheet, mLevelManager->GetLevel());
	mEnemy->Initalise(mMarineSheet, mAlienSheet, mMarkerSheet, mHealthSheet, mLevelManager->GetLevel());
	mCamera->SetCameraBounds(mLevelManager->GetLevel()->GetLevelWidth(), mLevelManager->GetLevel()->GetLevelHeight());
	mCamera->SetScrollSpeed(5.0f);

	while(!mSystem.Done())
	{
		srand(time(NULL));
		mThisTime = SDL_GetTicks();
		float dt = (float)(mThisTime - mLastTime) / 1000;
		mLastTime = mThisTime;

		if(keys[SDLK_ESCAPE])
		{
			break;
		}

		Update(dt);
		Draw();
	}

}

void Game::Update(float dt)
{
	mCamera->Update();
	mMouse.Update(mSystem.GetEvent(), mCamera, mPlayer, mEnemy );

	//mMenu->Update(0, &mMouse);
	mLevelManager->Update(dt);
	mPlayer->Update(dt , mEnemy, mLevelManager->GetLevel(), mCamera);
	mEnemy->Update(dt, mPlayer, mCamera, mLevelManager->GetLevel());

}

void Game::Draw()
{
	//temp background till level is implemented
	//SDL_BlitSurface(mTempBackground, &mCamera->GetCamera(), mBuffer, NULL);

	mMouse.Draw( mBuffer ); 

	//mMenu->Draw(mBuffer);
	mLevelManager->Draw( mBuffer, mCamera );
	mEnemy->Draw( mBuffer, mCamera );
	mPlayer->Draw( mBuffer, mCamera );

	SDL_Flip(mBuffer);
	SDL_FillRect(mBuffer, NULL, SDL_MapRGB(mBuffer->format, 0.0f, 0.0f, 0.0f));
}

void Game::Shutdown()
{
	mShutdown = true;

	delete mCamera;
	delete mPlayer;
	delete mEnemy;
	delete mMenu;
	delete mLevelManager;

	FreeSurface(mMarineSheet);
	FreeSurface(mAlienSheet);
	FreeSurface(mMarkerSheet);
	FreeSurface(mTempBackground);
	FreeSurface(mTileSheet);

	mSystem.Shutdown();
}

SDL_Surface* Game::LoadImage(std::string filename)
{
	SDL_Surface* loadedImage = SDL_LoadBMP(filename.c_str());
	SDL_Surface* optimizedImage = NULL;

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
	}

	SDL_FreeSurface(loadedImage);

	return optimizedImage;
}