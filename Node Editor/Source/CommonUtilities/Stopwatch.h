#pragma once
#include <chrono>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	class Stopwatch
	{
	public:
		Stopwatch& Init();
		void Update();
		float Elapsed();
		void Start();
		void Resume();
		void Stop();
		[[nodiscard]] bool IsCounting() const;
	private:
		bool myIsCounting;
		std::chrono::high_resolution_clock::time_point myStartTime;
		std::chrono::high_resolution_clock::time_point myStopTime;
		std::chrono::high_resolution_clock::time_point myCurrentTime;
		std::chrono::duration<float> mySkippedTime;
	};
}
