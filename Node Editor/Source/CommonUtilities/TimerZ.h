#pragma once
#include "Stopwatch.h"

namespace CommonUtilities
{
	class TimerZ : public Stopwatch
	{
	public:
		TimerZ& Init();
		[[nodiscard]] float GetDelay() const;
		void SetDelay(float aDelay);
		bool IsDone();
		float TimeLeft();
		float TimePassed();
		float Percent();
	private:
		float myDelay;
	};
}
