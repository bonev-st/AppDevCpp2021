/*
 * Dimention.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Dimention.hpp"

const Dimention Dimentions::ZERO = Dimention(0,0);
const Dimention Dimentions::UNDEFINED = Dimention(1000000, 1000000);

Dimention::Dimention(std::int32_t w, std::int32_t h) :
	m_W(w)
,	m_H(h)
{

}
