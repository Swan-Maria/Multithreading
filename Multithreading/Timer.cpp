#include "Timer.h"
#include <iostream>

Timer::Timer() : start_time_(std::chrono::high_resolution_clock::now())
{
}

Timer::~Timer()
{
	stop();
}

void Timer::stop()
{
	auto end_time = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();

	auto duration = end - start;
	double s = duration * 0.001 * 0.001;

	std::cout << "\nDuration of code working is " << s << " seconds\n";
}