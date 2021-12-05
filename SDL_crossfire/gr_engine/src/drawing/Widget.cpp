/*
 * Widget.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#include "gr_engine/drawing/Widget.hpp"

#include <iostream>

#include "gr_engine/managers/DrawMgr.hpp"
#include "utils/geometry/Geometry.hpp"

void Widget::invalidate() {
	m_DrawParams.m_Invalidate = true;
}

bool Widget::isInvalidate() const {
	return m_DrawParams.m_Invalidate;
}

void Widget::draw() {
	m_DrawParams.m_Invalidate = false;
	if(m_Visible) {
		DrawMgrInst::getInstance()->draw(m_DrawParams);
	}
}

void Widget::setVisible(bool visible) {
	m_Visible = visible;
	invalidate();
}

bool Widget::getVisible() const {
	return m_Visible;
}

void Widget::setPosition(const Point& pos) {
	m_DrawParams.m_DstRect.m_Pos = pos;
}

void Widget::setPosition(const Point& pos, const Dimention &dim) {
	m_DrawParams.m_DstRect.m_Pos = pos;
	m_DrawParams.m_DstRect.m_W = dim.m_W;
	m_DrawParams.m_DstRect.m_H = dim.m_H;
}

void Widget::setPositionCenter(const Point& pos) {
	m_DrawParams.m_DstRect.setToCenter(pos);
}

Point Widget::getPosition() const {
	return m_DrawParams.m_DstRect.m_Pos;
}

Point Widget::getPositionCenter() const {
	return m_DrawParams.m_DstRect.getCenter();
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

Dimention Widget::getDimentions() const {
	return Dimention(getWidth(), getHeight());
}

int32_t Widget::getWidth() const {
	return m_DrawParams.m_DstRect.m_W;
}

int32_t Widget::getHeight() const {
	return m_DrawParams.m_DstRect.m_H;
}

int32_t Widget::getX() const {
	return m_DrawParams.m_DstRect.m_Pos.m_X;
}

int32_t Widget::getY() const {
	return m_DrawParams.m_DstRect.m_Pos.m_Y;
}

int32_t Widget::getBottom() const {
	return m_DrawParams.m_DstRect.m_Pos.m_Y + m_DrawParams.m_DstRect.m_H;
}

int32_t Widget::getRight() const {
	return m_DrawParams.m_DstRect.m_Pos.m_X + m_DrawParams.m_DstRect.m_W;
}

Rectangle Widget::getRectangle() const {
	return m_DrawParams.m_DstRect;
}

void Widget::setRectangle(const Rectangle rect) {
	m_DrawParams.m_DstRect = rect;
}

void Widget::setOpacity(int32_t opacity) {
	if(BlendMode_t::NONE == m_DrawParams.m_BlendMode) {
		std::cerr << "Widget::setOpacity() failed. Set blend mode first" << std::endl;
		return;
	}
	m_DrawParams.m_Opacity = opacity;
	if(!DrawMgrInst::getInstance()->setAlpha(m_DrawParams)) {
		std::cerr << "Widget::setOpacity().DrawMgrInst::getInstance()->setAlpha() failed." << std::endl;
	}
	invalidate();
}

int32_t Widget::getOpacity() const {
	return m_DrawParams.m_Opacity;
}

bool Widget::isAlphaModulationActivate() const {
	return BlendMode_t::NONE != m_DrawParams.m_BlendMode;
}

void Widget::activateAlphaModulation() {
	if(BlendMode_t::NONE == m_DrawParams.m_BlendMode) {
		m_DrawParams.m_BlendMode = BlendMode_t::BLEND;
		if(!DrawMgrInst::getInstance()->setBlendMode(m_DrawParams)) {
			std::cerr << "Widget::activateAlphaModulation().setBlendMode() failed." << std::endl;
		}
	} else {
		std::cerr << "Widget::activateAlphaModulation() failed. BlendMode already enabled" << std::endl;
	}
}

void Widget::deactivateAlphaModulation() {
	if(BlendMode_t::NONE != m_DrawParams.m_BlendMode) {
		m_DrawParams.m_BlendMode = BlendMode_t::NONE;
		if(!DrawMgrInst::getInstance()->setBlendMode(m_DrawParams)) {
			std::cerr << "Widget::deactivateAlphaModulation().setBlendMode() failed." << std::endl;
		}
	} else {
		std::cerr << "Widget::deactivateAlphaModulation() failed. BlendMode already disabled" << std::endl;
	}
}

void Widget::setFlipMode(FlipMode_t flip) {
	m_DrawParams.m_FlipMode	= flip;
	invalidate();
}

void Widget::setRotation(double angle) {
	m_DrawParams.m_Angle = angle;
	invalidate();
}

double Widget::getRotation() const {
	return m_DrawParams.m_Angle;
}

void Widget::rotate(double delta) {
	m_DrawParams.m_Angle += delta;
	invalidate();
}

void Widget::rotateRight(double delta) {
	rotate(delta);
}

void Widget::rotateLeft(double delta) {
	rotate(-delta);
}

void Widget::setRotationCenter(const Point& point) {
	m_DrawParams.m_RotationCenter = point;
	invalidate();
}

const Point& Widget::getRotationCenter() const {
	return m_DrawParams.m_RotationCenter;
}

bool Widget::isContains(const Point &pos) const {
	return m_DrawParams.m_DstRect.isInside(pos);
}

bool Widget::isContains(const Rectangle &rec) const {
	return m_DrawParams.m_DstRect.isToched(rec);
}
