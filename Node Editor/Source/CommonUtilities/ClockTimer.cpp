#include "pch.h"
#include "ClockTimer.h"

CommonUtilities::ClockTimer::ClockTimer(float aTime)
{
	myTime = aTime;
	Start();
}

void CommonUtilities::ClockTimer::Update()
{
	if (myPaused)
	{
		//TODO: ändra till att endast räkna från pausen
		//TODO: Använd inte Update.
		const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(myStartTime - myCurrentTime);
		myPauseDuration += static_cast<float>(ms.count());
	}
}

void CommonUtilities::ClockTimer::Start()
{
	myStartTime = std::chrono::high_resolution_clock::now();
	myCurrentTime = std::chrono::high_resolution_clock::now();
	myPauseDuration = 0;
}

void CommonUtilities::ClockTimer::Stop()
{
}

void CommonUtilities::ClockTimer::Pause()
{
	myPaused = true;
}

void CommonUtilities::ClockTimer::Resume()
{
	myPaused = false;
}

void CommonUtilities::ClockTimer::Reset()
{
	Start();
}

void CommonUtilities::ClockTimer::SetTime(const float someSeconds)
{
	myTime = someSeconds;
}

float CommonUtilities::ClockTimer::GetTimeLeft()
{
	const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(myStartTime - myCurrentTime);
	return myTime - ms.count() - myPauseDuration;
}
