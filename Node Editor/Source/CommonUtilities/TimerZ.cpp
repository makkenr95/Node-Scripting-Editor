#include "pch.h"
#include "TimerZ.h"
#include "Utilis.hpp"

CommonUtilities::TimerZ& CommonUtilities::TimerZ::Init()
{
	Stopwatch::Init();
	SetDelay(0);
	return *this;
}

float CommonUtilities::TimerZ::GetDelay() const
{
	return myDelay;
}

void CommonUtilities::TimerZ::SetDelay(const float aDelay)
{
	myDelay = aDelay;
}

bool CommonUtilities::TimerZ::IsDone()
{
	return Elapsed() >= myDelay;
}

float CommonUtilities::TimerZ::TimeLeft()
{
	return myDelay - TimePassed();
}

float CommonUtilities::TimerZ::TimePassed()
{
	return CU::Clamp(Elapsed(), 0.0f, myDelay);
}

float CommonUtilities::TimerZ::Percent()
{
	return TimePassed() / myDelay;
}
