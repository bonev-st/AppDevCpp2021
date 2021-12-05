/*
 * TextureContainer.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "gr_engine/widgets/WidgetContainer.hpp"

#include <algorithm>
#include <iostream>

#include "utils/drawing/Color.hpp"
#include "gr_engine/config/DebugCfg.hpp"

bool WidgetContainer::init(const Dimention& dimension, const Point & pos) {
	if(!m_Texture.create(dimension, Colors::FULL_TRANSPARENT, pos)){
		std::cerr << "RGB_Texture::create() failed" << std::endl;
	}
	return true;
}

void WidgetContainer::add(Widget * widget) {
	m_Container.push_back(widget);
	m_Texture.invalidate();
}

bool WidgetContainer::remove(const Widget * widget) {
	auto it = std::find(m_Container.begin(), m_Container.end(), widget);
	if(m_Container.end() == it) {
		std::cerr << "Can't find widget" << std::endl;
		return false;
	}
	m_Container.erase(it);
	m_Texture.invalidate();
	return true;
}

bool WidgetContainer::getVisible() const {
	return m_Texture.getVisible();
}

void WidgetContainer::setVisible(bool val) {
	m_Texture.setVisible(val);
}

void WidgetContainer::draw() {
	if(!m_Texture.getVisible()) {
		return;
	}
	if(!m_Texture.isInvalidate()) {
		for(const auto e : m_Container) {
			if(e->isInvalidate()) {
				if(DebugCfg::m_Enable) {
					if(!resetTimer()) {
						std::cerr << "WidgetContainer::draw() resetTimer() failed" << std::endl;
						return;
					}
				}
				m_Texture.invalidate();
				break;
			}
		}
	}
	if(m_Texture.isInvalidate()) {
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

bool WidgetContainer::resetTimer() {
	if(!m_DebugTimer.isRunning()) {
		m_Texture.setColor(Colors::DEBUG_BACKGROUND);
	}
	if(!m_DebugTimer.start(DebugCfg::m_TimerPeiod, Timer2::TimerMode_t::ONESHOT, [this](Timer2::TimerHandler_t handler) {
		if(this->m_DebugTimer != handler) {
			std::cerr << "Handler and m_DebugTimer not match" << std::endl;
		}
		m_Texture.setColor(Colors::FULL_TRANSPARENT);
	})) {
		std::cerr << "Timer start() failed" << std::endl;
		return false;
	}
	return true;
}

