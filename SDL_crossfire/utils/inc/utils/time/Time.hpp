/*
 * Time.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef UTILS_TIME_TIME_HPP_
#define UTILS_TIME_TIME_HPP_

#include <chrono>

class Time {
public:
	typedef std::chrono::seconds Seconds_t;
	typedef std::chrono::milliseconds Milliseconds_t;
	typedef std::chrono::microseconds Microseconds_t;
	typedef std::chrono::nanoseconds Nanoseconds_t;

	void start();

	template<class T = Microseconds_t>
	int64_t toTime() const {
		return std::chrono::duration_cast<T>(m_Now - m_ElapsedTime).count();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_Now = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> m_ElapsedTime;
};

#endif /* UTILS_TIME_TIME_HPP_ */
