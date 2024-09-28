#pragma once
#include <chrono>
#include <iostream>

namespace Trengine {
	template<typename Fn>
	class Timer {
	private:
		const char* name;
		std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
		bool stopped;
		Fn pushToRecordFunc;
	public:
		Timer(const char* name, Fn&& pushToRecordFunc) 
			: name(name), pushToRecordFunc(pushToRecordFunc), stopped(false)
		{
			startTimepoint = std::chrono::high_resolution_clock::now();
		}

		void stop() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			stopped = true;
	
			pushToRecordFunc({ this->name, (end - start) * 0.001f });
		}

		~Timer() {
			if (!stopped)
				stop();
		}
	};

#define SET_TIMER_SCOPE(timerName) Trengine::Timer t(timerName, [&](ProfileResult profileResult) {profileResults.push_back(profileResult); });

}