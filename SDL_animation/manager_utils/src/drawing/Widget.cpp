/*
 * Widget.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/Widget.hpp"

#include <iostream>

#include "manager_utils/managers/DrawMgr.hpp"

DrawMgr *& Widget::m_DrawMgr = G_pDrawMgr;

void Widget::draw() {
	if(m_Visible) {
		m_DrawMgr->draw(m_DrawParams);
	}
}

void Widget::setVisible(bool visible) {
	m_Visible = visible;
}

void Widget::setPosition(const Point& pos) {
	m_DrawParams.m_DstRect.m_Pos = pos;
}

const Point& Widget::getPosition() const {
	return m_DrawParams.m_DstRect.m_Pos;
}

void Widget::setX(int32_t x) {
	m_DrawParams.m_DstRect.m_Pos.m_X = x;
}

void Widget::setY(int32_t y) {
	m_DrawParams.m_DstRect.m_Pos.m_Y = y;
}

void Widget::moveRight(int32_t val) {
	moveH(val);
}

void Widget::moveLeft(int32_t val) {
	moveH(-val);
}

void Widget::moveUp(int32_t val) {
	moveV(-val);
}

void Widget::moveDown(int32_t val) {
	moveV(val);
}

void Widget::moveH(int32_t val) {
	m_DrawParams.m_DstRect.m_Pos.m_X += val;
}

void Widget::moveV(int32_t val) {
	m_DrawParams.m_DstRect.m_Pos.m_Y += val;
}

void Widget::setOpacity(int32_t opacity) {
	if(BlendMode_t::NONE == m_DrawParams.m_BlendMode) {
		std::cerr << "Widget::setOpacity() failed. Set blend mode first" << std::endl;
		return;
	}
	m_DrawParams.m_Opacity = opacity;
	if(!m_DrawMgr->setAlpha(m_DrawParams)) {
		std::cerr << "Widget::setOpacity().m_DrawMgr->setAlpha() failed." << std::endl;
	}
}

int32_t Widget::getOpacity() const {
	return m_DrawParams.m_Opacity;
}

void Widget::activateAlphaModulation() {
	if(BlendMode_t::NONE == m_DrawParams.m_BlendMode) {
		m_DrawParams.m_BlendMode = BlendMode_t::BLEND;
		if(!m_DrawMgr->setBlendMode(m_DrawParams)) {
			std::cerr << "Widget::activateAlphaModulation().setBlendMode() failed." << std::endl;
		}
	} else {
		std::cerr << "Widget::activateAlphaModulation() failed. BlendMode already enabled" << std::endl;
	}
}

void Widget::deactivateAlphaModulation() {
	if(BlendMode_t::NONE != m_DrawParams.m_BlendMode) {
		m_DrawParams.m_BlendMode = BlendMode_t::NONE;
		if(!m_DrawMgr->setBlendMode(m_DrawParams)) {
			std::cerr << "Widget::deactivateAlphaModulation().setBlendMode() failed." << std::endl;
		}
	} else {
		std::cerr << "Widget::deactivateAlphaModulation() failed. BlendMode already disabled" << std::endl;
	}
}

void Widget::scale(double val) {
	m_DrawParams.m_DstRect.scale(val);
}

void Widget::setFlipMode(FlipMode_t flip) {
	m_DrawParams.m_FlipMode	= flip;
}

void Widget::setRotation(double angle) {
	m_DrawParams.m_Angle = angle;
}

double Widget::getRotation() const {
	return m_DrawParams.m_Angle;
}

void Widget::rotate(double delta) {
	m_DrawParams.m_Angle += delta;
}

void Widget::rotateRight(double delta) {
	rotate(delta);
}

void Widget::rotateLeft(double delta) {
	rotate(-delta);
}

void Widget::setRotationCenter(const Point& point) {
	m_DrawParams.m_RotationCenter = point;
}

const Point& Widget::getRotationCenter() const {
	return m_DrawParams.m_RotationCenter;
}
