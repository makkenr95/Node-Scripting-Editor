#include "pch.h"
#include "Stopwatch.h"

CommonUtilities::Stopwatch& CommonUtilities::Stopwatch::Init()
{
	myIsCounting = true;
	myStartTime = std::chrono::high_resolution_clock::time_point::min();
	myStopTime = std::chrono::high_resolution_clock::time_point::min();
	mySkippedTime = std::chrono::duration<float>::zero();
	return *this;
}

void CommonUtilities::Stopwatch::Update()
{
	myCurrentTime = std::chrono::high_resolution_clock::now();
}

float CommonUtilities::Stopwatch::Elapsed()
{
	return (static_cast<std::chrono::duration<float>>((myIsCounting ? myCurrentTime : myStopTime) - myStartTime -
		mySkippedTime).count());
}

void CommonUtilities::Stopwatch::Start()
{
	myStartTime = myCurrentTime;
	mySkippedTime = std::chrono::duration<float>::zero();
	myIsCounting = true;
}

void CommonUtilities::Stopwatch::Resume()
{
	mySkippedTime += myCurrentTime - myStopTime;
	myIsCounting = true;
}

void CommonUtilities::Stopwatch::Stop()
{
	if (!myIsCounting)
		return;
	myStartTime = myCurrentTime;
	myIsCounting = false;
}

bool CommonUtilities::Stopwatch::IsCounting() const
{
	return myIsCounting;
}
