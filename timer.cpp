// By Emil Ernerfeldt 2012-2016
// LICENSE:
//   This software is dual-licensed to the public domain and under the following
//   license: you are granted a perpetual, irrevocable license to copy, modify,
//   publish, and distribute this file as you see fit.

#include "timer.hpp"

namespace emilib {

static Timer s_sw;

Timer::Timer()
{
	reset();
}

double Timer::reset()
{
	auto now = Clock::now();
	auto dur = now - _start;
	_start = now;
	return 1e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
}

double Timer::secs() const
{
	return nanoseconds() * 1e-9;
}

unsigned long long Timer::nanoseconds() const
{
	auto dur = Clock::now() - _start;
	return std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
}

void Timer::set_secs(double s)
{
	set_nanoseconds(s * 1e9);
}

void Timer::set_nanoseconds(double ns_f)
{
	std::chrono::duration<int, std::nano> dur( (long long)ns_f );
	_start = Clock::now() - dur;
}

double Timer::current_time_secs()
{
	return s_sw.secs();
}

} // namespace emilib
