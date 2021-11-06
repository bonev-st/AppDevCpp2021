/*
 * DrawParams.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_DRAWPARAMS_HPP_
#define UTILS_DRAWING_DRAWPARAMS_HPP_

#include <cstdint>
#include <vector>

#include "utils/drawing/WidgetType.hpp"
#include "utils/drawing/BlendMode.hpp"
#include "utils/drawing/FlipMode.hpp"
#include "utils/drawing/Rectangle.hpp"
#include "utils/drawing/Dimention.hpp"

inline constexpr std::size_t INVALID_RESR_ID = -1;

struct DrawParams_t {
	std::size_t m_ResrId = INVALID_RESR_ID;
	int32_t m_Opacity = FULL_OPACITY;
	BlendMode_t m_BlendMode = BlendMode_t::NONE;
	Rectangle m_SrcRect = Rectangle::UNDEFINED;
	Rectangle m_DstRect = Rectangle::UNDEFINED;
	WidgetType_t m_WidgetType = WidgetType_t::UNKNOWN;
	Dimention m_Dimention = Dimention::ZERO;
	const std::vector<Rectangle> *m_Frames = nullptr;
	FlipMode_t m_FlipMode = FlipMode_t::NONE;
	double m_Angle = 0;
	Point m_RotationCenter = Point::UNDEFINED;
};

#endif /* UTILS_DRAWING_DRAWPARAMS_HPP_ */
