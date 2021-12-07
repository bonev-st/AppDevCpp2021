/*
 * RandomNumber.hpp
 *
 *  Created on: Dec 7, 2021
 *      Author: stanimir
 */

#ifndef UTILS_RANDOMNUMBER_HPP_
#define UTILS_RANDOMNUMBER_HPP_

#include <random>

class RandomNumber {
public:
	void init();
	template<typename T>
	T get(T min, T max);

private:
    std::mt19937 m_RandomGen;
};

template<typename T>
T RandomNumber::get(T min, T max) {
	std::uniform_int_distribution<T> dist{min, max};
	return dist(m_RandomGen);
}

#endif /* UTILS_RANDOMNUMBER_HPP_ */
