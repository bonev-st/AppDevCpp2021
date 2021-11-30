/*
 * ExplosionContainer.cpp
 *
 *  Created on: Nov 29, 2021
 *      Author: stanimir
 */

#include "game/widgets/ExplosionContainer.hpp"

#include <iostream>

bool ExplosionContainer::init(std::size_t img_id, double scale) {
	m_ImgId = img_id;
	m_Scale = scale;
	return true;
}

bool ExplosionContainer::show(Widget * src, const Callback_t & cb) {
	auto widget = std::make_shared<Data_t>();

	if(widget->m_Img.create(m_ImgId)) {
		std::cerr << "Image create failed" << std::endl;
		return false;
	}
	if(widget->m_Scale.init(m_Scale, &widget->m_Img)) {
		std::cerr << "ScaleTexture create failed" << std::endl;
		return false;
	}
	widget->m_CB = cb;
	widget->m_Widget = src;
	auto handler = m_Container.add(widget);
	auto callback = std::bind(&ExplosionContainer::onAnimationTick, this, std::placeholders::_1, std::placeholders::_2);
	if(widget->m_Img.init(TIMER_PERIOD, SpriteMode_t::FORWARD, callback, (void *)handler)) {
		std::cerr << "Image create failed" << std::endl;
		return false;
	}
	return true;
}

void ExplosionContainer::draw() {
	for(const auto & e : m_Container) {
		e->m_Scale.draw();
	}
}

void ExplosionContainer::onAnimationTick(std::size_t frame, void * param) {
	std::shared_ptr<Data_t> * p_data = m_Container.get(reinterpret_cast<size_t>(param));
	if(p_data && *p_data) {
		std::cerr << "ExplosionContainer::onAnimationTick() invalid handler" << std::endl;
		return;
	}
	auto &data = *(*p_data).get();
	if(!frame) {
		if(data.m_CB) {
			data.m_CB(data.m_Widget);
		}

	}
	auto alpha = ZERO_OPACITY;
	if(HIDE_FAME > frame) {
		double k = static_cast<double>(frame);
		k /= HIDE_FAME;
		k = 1 - k;
		k *= FULL_OPACITY;
		alpha = static_cast<int32_t>(k);
	}
	data.m_Img.setOpacity(alpha);
}
