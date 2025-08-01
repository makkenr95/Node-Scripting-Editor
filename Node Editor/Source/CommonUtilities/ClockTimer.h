#pragma once
#include <chrono>

namespace CommonUtilities
{
	class ClockTimer
	{
	public:
		ClockTimer(float aTime);
		void Update();
		void Start();
		void Stop();
		void Pause();
		void Resume();
		void Reset();
		void SetTime(const float someSeconds);
		float GetTimeLeft();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> myStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTime;
		float myPauseDuration = 0;
		float myTime = 0;
		bool myPaused;
	};
}
