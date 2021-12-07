/*
 * RandomNumber.cpp
 *
 *  Created on: Dec 7, 2021
 *      Author: stanimir
 */

#include "utils/RandomNumber.hpp"

void RandomNumber::init() {
	std::random_device rd;
	m_RandomGen.seed(rd());
}
