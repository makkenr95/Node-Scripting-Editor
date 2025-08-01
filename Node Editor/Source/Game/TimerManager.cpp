#include "stdafx.h"
#include "TimerManager.h"

void TimerManager::Update()
{
	myHeartbeatTimer.Update();

	auto It = myTimers.begin();
	while(It != myTimers.end())
	{
		It->second.TimeElapsed += myHeartbeatTimer.GetDeltaTime();
		if(It->second.TimeElapsed >= It->second.Duration)
		{
			It->second.Callback();
			if(!It->second.IsRepeating)
			{
				It->second.Callback = nullptr;
				It = myTimers.erase(It);
				continue;
			}
			It->second.TimeElapsed -= It->second.Duration;
		}

		++It;
	}
}

TimerHandle TimerManager::AddTimer(TimerCallback aCallback, float aDuration, bool shouldLoop)
{
	const TimerHandle newHandle = myIdCounter;
	myTimers.insert({ myIdCounter++, { std::move(aCallback), 0, aDuration, shouldLoop } });
	return newHandle;
}

bool TimerManager::ClearTimer(TimerHandle& aHandle)
{
	auto It = myTimers.find(aHandle.GetID());
	if(It != myTimers.end())
	{
		It->second.Callback = nullptr;
		myTimers.erase(It);
		return true;
	}

	return false;
}
