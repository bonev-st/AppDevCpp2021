/*
 * TextureContainer.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "game/widgets/WidgetContainer.hpp"

#include <algorithm>
#include <iostream>

#include "utils/drawing/Color.hpp"

bool WidgetContainer::init(const Dimention& dimension, const Point & pos) {
	if(!m_Texture.create(dimension, Colors::FULL_TRANSPARENT, pos)){
		std::cerr << "RGB_Texture::create() failed" << std::endl;
	}
	return true;
}

void WidgetContainer::add(Widget * widget) {
	m_Container.push_back(widget);
	m_Redraw = true;
}

bool WidgetContainer::remove(const Widget * widget) {
	auto it = std::find(m_Container.begin(), m_Container.end(), widget);
	if(m_Container.end() == it) {
		std::cerr << "Can't find widget" << std::endl;
		return false;
	}
	m_Container.erase(it);
	m_Redraw = true;
	return true;
}

void WidgetContainer::draw() {
	if(!m_Redraw) {
		for(const auto e : m_Container) {
			if(e->isInvalidate()) {
				m_Redraw = true;
				break;
			}
		}
	}
	if(m_Redraw) {
		auto lock = m_Texture.getLock();
		if(nullptr == lock) {
			std::cerr << "Can't get widget lock" << std::endl;
			return;
		}
		for(const auto e : m_Container) {
			e->draw();
		}
	}
	m_Texture.draw();
}
