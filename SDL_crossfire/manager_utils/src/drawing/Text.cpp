/*
 * Text.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/Text.hpp"

#include <iostream>

#include "manager_utils/managers/ResMgr.hpp"

bool Text::create(const std::string &text, const Color &color, std::size_t font_id, const Point &pos) {
	if(WidgetType_t::UNKNOWN != m_DrawParams.m_WidgetType) {
		std::cerr << "Text::create failed. Text already created" << std::endl;
		return false;
	}
	m_Text   = text;
	m_Color  = color;
	m_FontId = font_id;
	return create(pos);
}

bool Text::setText(const std::string &text, const Point &pos) {
	if(text == m_Text) {
		if(Point::UNDEFINED != pos) {
			setPosition(pos);
		}
		return true;
	}
	m_Text = text;
	auto position = getPosition();
	if(Point::UNDEFINED != pos) {
		position = pos;
	}
	return create(position);
}

bool Text::setColor(const Color &color) {
	if(color == m_Color) {
		return true;
	}
	m_Color = color;
	auto position = getPosition();
	return create(position);
}

bool Text::create(const Point &pos) {
	if(!ResMgrInst::getInstance()->createText(m_Text, m_Color, m_FontId, m_DrawParams)) {
		std::cerr << "Text::create.createText() failed"<< std::endl;
		return false;
	}
	if(Point::UNDEFINED != pos) {
		setPosition(pos);
	}
	invalidate();
	return true;
}
