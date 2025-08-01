#pragma once
#include "Timer.h"

typedef std::function<void()> TimerCallback;

struct TimerHandle
{
private:
	friend class TimerManager;
	int ID = -1;

	TimerHandle(unsigned int anId) { ID = anId; }

public:
	[[nodiscard]] unsigned int GetID() const { return ID; }

	[[nodiscard]] bool IsValid() const { return ID >= 0; }
};

class TimerManager
{
	struct ManagedTimer
	{
		TimerCallback Callback;
		float TimeElapsed;
		float Duration;
		bool IsRepeating = false;
	};

	inline static std::unordered_map<unsigned int, ManagedTimer> myTimers;

	inline static Timer myHeartbeatTimer;
	inline static unsigned int myIdCounter = 0;

public:

	static void Update();
	static TimerHandle AddTimer(TimerCallback aCallback, float aDuration, bool shouldLoop = false);
	static bool ClearTimer(TimerHandle& aHandle);
};

