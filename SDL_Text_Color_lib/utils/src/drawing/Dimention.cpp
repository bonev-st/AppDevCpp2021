/*
 * Dimention.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Dimention.hpp"

const Dimention Dimention::ZERO = Dimention(0,0);
const Dimention Dimention::UNDEFINED = Dimention(1e6,1e6);

Dimention::Dimention(std::int32_t w, std::int32_t h) :
	m_W(w)
,	m_H(h)
{

}
