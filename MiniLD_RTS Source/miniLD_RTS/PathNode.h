#ifndef PATH_NODE_H
#define PATH_NODE_H

class PathNode
{
public:
	PathNode(int hValue, int id, float posX, float posY);
	~PathNode();

	void SetHvalue(float _hValue);
	void SetParent(bool _parent);
	int GetHvalue();
	bool GetParent();
	int GetId();
	float GetPosX();
	float GetPosY();
private:
	
	bool mParent;
	int mHvalue,
		mId,
		mPosX,
		mPosY;

};

#endif