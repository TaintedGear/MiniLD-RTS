#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Pause();
	void Stop();
	void UnPause();
	float GetTicks();
	void RegulateFPS(int fps);

	bool GetStarted();
	bool GetPaused();

private:

	int mCurrentTicks;
	int mStartTicks;
	int mPausedTicks;

	bool mStarted;
	bool mPaused;
};

#endif