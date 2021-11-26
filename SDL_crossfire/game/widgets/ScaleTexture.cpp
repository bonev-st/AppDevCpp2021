/*
 * ScaleTexture.cpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#include "game/widgets/ScaleTexture.hpp"

#include <iostream>
#include <cmath>

#include "utils/drawing/Color.hpp"

bool ScaleTexture::init(double scale_factor, Widget * scaled) {
	if(!scale_factor) {
		std::cerr << "Invalid scale factor" << std::endl;
		return false;
	}
	if(!scaled) {
		std::cerr << "Invalid scaled Widget" << std::endl;
		return false;
	}
	m_ScaleFactor = scale_factor;
	m_Scaled = scaled;
	reload();
	return true;
}

void ScaleTexture::reload() {
	Dimention dim = m_Scaled->getDimentions();
	dim.m_H = static_cast<int32_t>(std::round(dim.m_H * m_ScaleFactor));
	dim.m_W = static_cast<int32_t>(std::round(dim.m_W * m_ScaleFactor));
	auto rect = getRectangle();
	rect.m_H = dim.m_H;
	rect.m_W = dim.m_W;
	setRectangle(rect);
}

void ScaleTexture::draw() {
	if(getDebug() && m_Scaled->isInvalidate()) {
		if(m_DebugTimer.isRunning()) {
			if(!m_DebugTimer.start(DEBUG_TIMER_PERIOD, Timer2::TimerMode_t::ONESHOT, [this](Timer2::TimerHandler_t handler) {
				if(this->m_DebugTimer != handler) {
					std::cerr << "ScaleTexture::draw() m_DebugTimer.Callback() handler not match" << std::endl;
				}
				this->m_SkipDebugTimer = true;
				this->invalidate();
			})) {
				std::cerr << "ScaleTexture::draw() m_DebugTimer.start() failed" << std::endl;
			}
		} else {
			invalidate();
		}
	}
	if(RGB_Texture::m_DrawParams.m_Invalidate) {
		Dimention dim = m_Scaled->getDimentions();
		dim.m_H = static_cast<int32_t>(std::round(dim.m_H * m_ScaleFactor));
		dim.m_W = static_cast<int32_t>(std::round(dim.m_W * m_ScaleFactor));
		auto color = Colors::FULL_TRANSPARENT;
		if(getDebug() && !m_SkipDebugTimer) {
			color = Colors::DEBUG_BACKGROUND;
			if(!m_DebugTimer.start(DEBUG_TIMER_PERIOD, Timer2::TimerMode_t::ONESHOT, [this](Timer2::TimerHandler_t handler) {
				if(this->m_DebugTimer != handler) {
					std::cerr << "ScaleTexture::draw() m_DebugTimer.Callback() handler not match" << std::endl;
				}
				this->m_SkipDebugTimer = true;
				this->invalidate();
			})) {
				std::cerr << "ScaleTexture::draw() m_DebugTimer.start() failed" << std::endl;
			}
		}
		create(dim, color, getPosition());
		m_SkipDebugTimer = false;
		m_Scaled->invalidate();
	}
	if(m_Scaled->isInvalidate()) {
		auto lock = getLock();
		if(nullptr == lock) {
			std::cerr << "ScaleTexture::getLock() failed" << std::endl;
			return;
		}
		Rectangle rect_tmp = m_Scaled->getRectangle();
		const Dimention dim_scale = getDimentions();
		m_Scaled->setPosition(Point::ZERO, dim_scale);
		m_Scaled->draw();
		m_Scaled->setRectangle(rect_tmp);
	}
	RGB_Texture::draw();
}


