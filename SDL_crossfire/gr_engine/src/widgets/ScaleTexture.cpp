/*
 * ScaleTexture.cpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#include "gr_engine/widgets/ScaleTexture.hpp"

#include <iostream>
#include <cmath>

#include "utils/drawing/Color.hpp"

bool ScaleTexture::init(double scale_factor, Widget * scaled, const Color & color) {
	if(!scale_factor) {
		std::cerr << "Invalid scale factor" << std::endl;
		return false;
	}
	if(!scaled) {
		std::cerr << "Invalid scaled Widget" << std::endl;
		return false;
	}
	m_Color = color;
	m_ScaleFactor = scale_factor;
	m_Scaled = scaled;
	if(!createTexture()) {
		std::cerr << "createTexture() failed" << std::endl;
		return false;
	}
	return true;
}

void ScaleTexture::setPositionCenter(const Point& pos) {
	dim_update();
	RGB_Texture::setPositionCenter(pos);
}

void ScaleTexture::draw() {
	bool invalidate = m_Scaled->isInvalidate();
	if(invalidate && getDebug()) {
		if(!resetTimer()) {
			std::cerr << "ScaleTexture::draw() resetTimer() failed" << std::endl;
			return;
		}
	}
	if(invalidate) {
		if(!createTexture()) {
			std::cerr << "createTexture() failed" << std::endl;
			return;
		}
	}
	if(invalidate ||  RGB_Texture::isInvalidate()) {
		if(!redraw()) {
			std::cerr << "ScaleTexture::draw() redraw() failed" << std::endl;
			return;
		}
	}
	RGB_Texture::draw();
}

bool ScaleTexture::isInvalidate() const {
	return m_Scaled->isInvalidate() || RGB_Texture::isInvalidate();
}

void ScaleTexture::dim_update() {
	Dimention dim = m_Scaled->getDimentions();
	dim.m_H = static_cast<int32_t>(std::round(dim.m_H * m_ScaleFactor));
	dim.m_W = static_cast<int32_t>(std::round(dim.m_W * m_ScaleFactor));
	auto rect = getRectangle();
	rect.m_H = dim.m_H;
	rect.m_W = dim.m_W;
	setRectangle(rect);
}

bool ScaleTexture::createTexture() {
	dim_update();
	Dimention dim = getDimentions();
	auto color = m_DebugTimer.isRunning()?Colors::DEBUG_BACKGROUND:m_Color;
	if(!create(dim, color, getPosition())){
		std::cerr << "ScaleTexture::draw() RGB_Texture::create() failed" << std::endl;
	}
	return true;
}

bool ScaleTexture::resetTimer() {
	if(!m_DebugTimer.isRunning()) {
		setColor(Colors::DEBUG_BACKGROUND);
	}
	if(!m_DebugTimer.start(DEBUG_TIMER_PERIOD, Timer2::TimerMode_t::ONESHOT, [this](Timer2::TimerHandler_t handler) {
		if(this->m_DebugTimer != handler) {
			std::cerr << "Handler and m_DebugTimer not match" << std::endl;
		}
		this->setColor(this->m_Color);
	})) {
		std::cerr << "Timer start() failed" << std::endl;
		return false;
	}
	return true;
}

bool ScaleTexture::redraw() {
	auto lock = getLock();
	if(nullptr == lock) {
		std::cerr << "RGB_Texture::getLock() failed" << std::endl;
		return false;
	}
	Rectangle rect_tmp = m_Scaled->getRectangle();
	const Dimention dim_scale = getDimentions();
	m_Scaled->setPosition(Points::ZERO, dim_scale);
	m_Scaled->draw();
	m_Scaled->setRectangle(rect_tmp);
	return true;
}
