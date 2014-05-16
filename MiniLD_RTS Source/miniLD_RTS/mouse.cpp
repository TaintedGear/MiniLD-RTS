#include "Mouse.h"

Mouse::Mouse() : mWidth(32), mHeight(32), mScreenRegion(5.0f), mSelection(false), mMouseButtonIsDown(false),
	mStartPosX(0), mStartPosY(0), mEndPosX(0), mEndPosY(0)
{
	mGroupBox.x = 0;
	mGroupBox.y = 0;
	mGroupBox.w = 0;
	mGroupBox.h = 0;
	mCollisionBox.x = 0;
	mCollisionBox.y = 0;
	mCollisionBox.h = 0;
	mCollisionBox.w = 0;
}

Mouse::~Mouse()
{
}

void Mouse::Update( SDL_Event &event, Camera *camera, PlayerController *player,
		EnemyController *enemy)
{
	mSelection = false;

	mCollisionBox.h = mHeight;
	mCollisionBox.w = mWidth;
	if(event.type == SDL_MOUSEMOTION)
	{
		mCollisionBox.x = event.motion.x - (mCollisionBox.w / 2);
		mCollisionBox.y = event.motion.y - (mCollisionBox.h / 2);
	}

	switch(event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		PickSelection(event, camera, player);

		for(int i = 0; i < player->GetUnitAmount(); i++)
		{

			if((!mMouseButtonIsDown) && (event.button.button == SDL_BUTTON_LEFT))
			{
				mMouseButtonIsDown = true;
				mStartPosX = mCollisionBox.x;
				mStartPosY = mCollisionBox.y;
				mGroupBox.x = mCollisionBox.x;
				mGroupBox.y = mCollisionBox.y;
			}

				if(event.button.button == SDL_BUTTON_RIGHT)
				{
					bool collision = false;

					for(int j = 0; j < enemy->GetUnitAmount(); j++)
					{
						//Sets the target object to attack with the selected unit
						if ((player->GetUnit(i)->GetSelected()) &&
							(CheckCollision(mCollisionBox, enemy->GetUnit(j)->GetCollisionBox()) && 
							(!enemy->GetUnit(j)->GetDead())))
						{
							collision = true;
							player->GetUnit(i)->SetOrderState(2);
							player->GetUnit(i)->SetTargetX(enemy->GetUnit(j)->GetCollisionBox().x + camera->GetCamera().x);
							player->GetUnit(i)->SetTargetY(enemy->GetUnit(j)->GetCollisionBox().y + camera->GetCamera().y);
							player->GetUnit(i)->SetTargetObject(enemy->GetUnit(j));
						}
					}
					//Sets the target position to move the selected unit to that position
					if ((player->GetUnit(i)->GetSelected()) && (!collision) && (!player->GetUnit(i)->GetDead()))
					{
						player->GetUnit(i)->SetOrderState(1);
						player->GetUnit(i)->SetTargetX(mCollisionBox.x - (mCollisionBox.w / 2) + camera->GetCamera().x);
						player->GetUnit(i)->SetTargetY(mCollisionBox.y - (mCollisionBox.h / 2) + camera->GetCamera().y);
					}
				}
		}

		break;

	case SDL_MOUSEBUTTONUP:

		if((mMouseButtonIsDown) && (event.button.button = SDL_BUTTON_LEFT))
		{
			mMouseButtonIsDown = false;
	
			mGroupBox.w = mCollisionBox.x - mGroupBox.x;
			mGroupBox.h = mCollisionBox.y - mGroupBox.y;

			for(int i = 0; i < player->GetUnitAmount(); i++)
			{
				if(CheckCollision(mGroupBox,player->GetUnit(i)->GetCollisionBox()))
				{
					player->GetUnit(i)->SetSelected(true);
				}
			}

			mGroupBox.x = 0;
			mGroupBox.y = 0;
			mGroupBox.h = 0;
			mGroupBox.w = 0;
		}

		break;

	}

	PanCamera(camera);
}

void Mouse::Draw(SDL_Surface *buffer)
{
	int tempStart = mStartPosX;

	SDL_FillRect( buffer, &mCollisionBox, SDL_MapRGB(buffer->format, 100, 100, 20));

}

void Mouse::PickSelection(SDL_Event &event, Camera *camera,  PlayerController *player)
{
	for(int i = 0; i < player->GetUnitAmount(); i++)
	{

		if(CheckCollision(mCollisionBox, player->GetUnit(i)->GetCollisionBox()))
		{
			if((!mSelection) && (event.button.button == SDL_BUTTON_LEFT))
			{
				mSelection = true;
				player->GetUnit(i)->SetSelected(true);
			}
		}
		else
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				player->GetUnit(i)->SetSelected(false);
				mSelection = false;
			}
		}
	}
}

void Mouse::GroupSelection(SDL_Event &event, Camera *camera,  PlayerController *player)
{

}


void Mouse::PanCamera(Camera *camera)
{
	//Finds percentage of the screen
	float screenPerX = PercentageOf(camera->GetCamera().w, mScreenRegion);
	float screenPerY = PercentageOf(camera->GetCamera().h, mScreenRegion);

	if(mCollisionBox.x + (mCollisionBox.w / 2) <= 0 + screenPerX)
	{
		camera->SetPosX(camera->GetPosX() - camera->GetScrollSpeed());
	}
	if(mCollisionBox.x + (mCollisionBox.w / 2) >= camera->GetCamera().w - screenPerX)
	{
		camera->SetPosX(camera->GetPosX() + camera->GetScrollSpeed());
	}
	if(mCollisionBox.y + (mCollisionBox.h / 2) <= 0 + screenPerY)
	{
		camera->SetPosY(camera->GetPosY() - camera->GetScrollSpeed());
	}
	if(mCollisionBox.y + (mCollisionBox.h / 2) >= camera->GetCamera().h - screenPerY)
	{
		camera->SetPosY(camera->GetPosY() + camera->GetScrollSpeed());
	}
}

void Mouse::SelectionBox(SDL_Surface *buffer, int x, int y)
{
	Uint32* pixels = (Uint32*)buffer->pixels;
	Uint32* pixel = pixels+(y*buffer->pitch)/4+x;
	*pixel=SDL_MapRGB(buffer->format,0xFF,0xFF,0xFF);
}