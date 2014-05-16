#include "PathNode.h"

PathNode::PathNode(int hValue, int id, float posX, float posY) : mHvalue(hValue), mId(id), mPosX(posX), mPosY(posY)
{
}
PathNode::~PathNode()
{
}

void PathNode::SetHvalue(float _hValue)
{
	mHvalue = _hValue;
}
void PathNode::SetParent(bool _parent)
{
	mParent = _parent;
}
int PathNode::GetHvalue()
{
	return mHvalue;
}
int PathNode::GetId()
{
	return mId;
}
bool PathNode::GetParent()
{
	return mParent;
}
float PathNode::GetPosX()
{
	return mPosX;
}
float PathNode::GetPosY()
{
	return mPosY;
}