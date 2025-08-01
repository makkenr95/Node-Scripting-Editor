#include "pch.h"
#include "Timer.h"

CommonUtilities::Timer::Timer()
{
	myStartTime = myClock.now();
	myCurrentTime = myStartTime;
	myPreviousTime = myClock.now();
}

void CommonUtilities::Timer::Update()
{
	myPreviousTime = myCurrentTime;
	myCurrentTime = myClock.now();
}

float CommonUtilities::Timer::GetDeltaTime() const
{
	std::chrono::duration<float> duration = myCurrentTime - myPreviousTime;
	return duration.count();
}

double CommonUtilities::Timer::GetTotalTime() const
{
	std::chrono::duration<double> duration = myCurrentTime - myStartTime;
	return duration.count();
}
