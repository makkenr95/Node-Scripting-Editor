#pragma once
#include <chrono>

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;
		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		std::chrono::high_resolution_clock myClock;
		std::chrono::time_point<std::chrono::high_resolution_clock> myStartTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> myPreviousTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTime;
	};
}

namespace CU = CommonUtilities;
