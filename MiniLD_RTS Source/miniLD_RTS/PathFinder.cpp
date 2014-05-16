#include "PathFinder.h"

PathFinder::PathFinder() : mStraightCost(10), mDiagonalCost(14), mTargetFound(false), 
	mCurrentId(0), mTargetId(0)
{
}

PathFinder::~PathFinder()
{
	Reset();
	//delete mNewNode;
}


void PathFinder::FindTarget(float targetX, float targetY, Level *level)
{
	SDL_Rect targetRect;
	targetRect.x = targetX;
	targetRect.y = targetY;
	targetRect.h = 32;
	targetRect.w = 32;


	//Finds the target tile that the unit needs to get to
	for(unsigned int i = 0; i < level->GetFloorTileAmount(); i++)
	{
		if(CheckCollision(targetRect, level->GetFloorTile(i)->GetCollisionBox()))
		{
			mTargetId = level->GetFloorTile(i)->GetTileId();
			break;
		}
		else
		{
			mTargetFound = false;
		}
	}
	
	//Sets up all the nodes of the floor
	for(unsigned int i = 0; i < level->GetFloorTileAmount(); i++)
	{
		int hValue = ( level->GetFloorTile(mTargetId)->GetPosX() - level->GetFloorTile(i)->GetPosX()) +
			(level->GetFloorTile(mTargetId)->GetPosY() - level->GetFloorTile(i)->GetPosY());

		mNewNode = NULL;
		mNewNode = new PathNode(hValue, 
			level->GetFloorTile(i)->GetTileId(),
			level->GetFloorTile(i)->GetPosX(),
			level->GetFloorTile(i)->GetPosY());

		mNodes.push_back(mNewNode);
	}

	mTargetFound = true;
}

void PathFinder::MoveToNextNode(SDL_Rect unit, float &moveX, float &moveY, Level *level)
{
	//Finds the currTile the unit is on
	int current = 0;
	for(unsigned int i = 0; i < level->GetFloorTileAmount(); i++)
	{
		if(CheckCollision(unit, level->GetFloorTile(i)->GetCollisionBox()))
		{
			mCurrentId = level->GetFloorTile(i)->GetTileId();

			mClosedList.push_back(mCurrentId);

			break;
		}
	}

	//make this better
	int width = level->GetLevelWidth();

	mOpenList.push_back(mCurrentId - width - 1);
	mOpenList.push_back(mCurrentId - width);
	mOpenList.push_back(mCurrentId - width + 1);
	mOpenList.push_back(mCurrentId - 1);
	mOpenList.push_back(mCurrentId + 1);
	mOpenList.push_back(mCurrentId + width- 1);
	mOpenList.push_back(mCurrentId + width);
	mOpenList.push_back(mCurrentId + width + 1);

	for(unsigned int i = 0; i < mOpenList.size(); i++)
	{
		if(i == 1 || i == 3 || i == 4 || i == 6)
		{
			mMoveCost.push_back(mNodes[mOpenList[i]]->GetHvalue() + mStraightCost);
		}
		else
		{
			mMoveCost.push_back(mNodes[mOpenList[i]]->GetHvalue() + mDiagonalCost);
		}
	}

	
	int bestId = 0;
	int smallestMove = mMoveCost[0];
	
	for(unsigned int i = 1; i < mMoveCost.size(); i++)
	{
		if((mMoveCost[i] < smallestMove) && (mMoveCost[i] > 0))
		{
			smallestMove = mMoveCost[i];
			bestId = i;
		}
	}

	moveX = mNodes[mOpenList[bestId]]->GetPosX();
	moveY = mNodes[mOpenList[bestId]]->GetPosY();

	//mOpenList.erase(mOpenList.begin()+bestId);
}

void PathFinder::Reset()
{
	mMoveCost.clear();
	mOpenList.clear();
	mClosedList.clear();

	//for(unsigned int i = 0; i < mNodes.size(); i++)
	//{
	//	delete mNodes[i];
	//}

	//mTargetFound = false;
}
bool PathFinder::GetTargetFound()
{
	return mTargetFound;
}