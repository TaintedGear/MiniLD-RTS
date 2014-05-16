#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <iostream>
#include <vector>
#include "Level.h"
#include "PathNode.h"

using std::vector;

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void FindTarget(float targetX, float targetY, Level *level);
	void MoveToNextNode(SDL_Rect unit, float &moveX, float &moveY, Level *level);
	void Reset();

	bool GetTargetFound();
private:

	bool mTargetFound;

	int mCurrentId;
	int mTargetId;
	int mStraightCost;
	int mDiagonalCost;

	PathNode *mNewNode;
	vector<PathNode *> mNodes;
	vector<int> mHeurVal;
	vector<int> mMoveCost;
	vector<int> mOpenList;
	vector<int> mClosedList;
	
};
#endif