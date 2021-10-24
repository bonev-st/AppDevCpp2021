/*
 * Game.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Game.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "sdl_utils/InputEvent.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"
#include "utils/drawing/DrawParams.hpp"
#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

bool Game::init(const GameConfig::Config_t & cfg, const ImageContainer * img_if, TextContainer * text_if) {
	assert(img_if);
	assert(text_if);
	m_ImageContainerIF = img_if;
	m_TextContainerIF = text_if;
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "Game::init::loadKeys() failed." << std::endl;
		return false;
	}
	if(!initImgs()) {
		std::cerr << "Game::init::initImgs() failed." << std::endl;
		return false;
	}
	std::for_each(&m_Img[0], &m_Img[IMG_ARRAY_SIZE],
		[](DrawParams_t & e) {
			e.m_WidgetType = WidgetType_t::IMAGE;
		}
	);
	std::for_each(&m_Text[0], &m_Text[IMG_ARRAY_SIZE],
		[](DrawParams_t & e) {
			e.m_WidgetType = WidgetType_t::TEXT;
		}
	);
	m_Img[IMG_BACKGROUND_INDX].m_ResrId = ResurcesId::IDLE_IMG;
	m_Img[IMG_L2_INDX].m_ResrId = ResurcesId::L2_IMG;

	if(!loadImgDimention()) {
		std::cerr << "Game::init::loadImgDimention() failed." << std::endl;
		return false;
	}
	if(!createTexts()) {
		std::cerr << "Game:::init::createTexts() failed." << std::endl;
		return false;
	}
	return true;
}

bool Game::events(const InputEvent & event, bool & exit) {
	const auto it = m_Keys.find(event.m_Key);
	if(m_Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return true;
}

bool Game::draw(std::vector<DrawParams_t> &out, bool &update) {
	if(GameConfig::KEY_UP_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_Y -= MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_DOWN_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_Y += MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_LEFT_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_X -= MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_RIGHT_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_X += MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_ZOOM_UP_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.scale(1.01);
		update = true;
	}
	if(GameConfig::KEY_MOVE_UP_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.m_Pos.m_Y -= MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_MOVE_DOWN_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.m_Pos.m_Y += MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_MOVE_LEFT_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.m_Pos.m_X -= MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_MOVE_RIGHT_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.m_Pos.m_X += MOVE_STEP;
		update = true;
	}
	if(GameConfig::KEY_ZOOM_UP_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.scale(1.01);
		update = true;
	}
	if(GameConfig::KEY_ZOOM_DOWN_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].m_DstRect.scale(0.99);
		update = true;
	}
	if(GameConfig::KEY_OPACITY_UP_MASK & m_KeysMask) {
		auto & opacity = m_Img[IMG_BACKGROUND_INDX].m_Opacity;
		opacity += 1;
		if(FULL_OPACITY < opacity) {
			opacity = FULL_OPACITY;
		} else {
			update = true;
		}
	}
	if(GameConfig::KEY_OPACITY_DOWN_MASK & m_KeysMask) {
		auto & opacity = m_Img[IMG_BACKGROUND_INDX].m_Opacity;
		opacity -= 1;
		if(ZERO_OPACITY > opacity) {
			opacity = ZERO_OPACITY;
		} else {
			update = true;
		}
	}
	bool dynamic_text_update = false;
	if(!updateDynamicText(dynamic_text_update)) {
		std::cerr << "Game::draw::updateDynamicText() failed." << std::endl;
		return false;
	}
	update |= dynamic_text_update | m_ForceUpdate;
	m_ForceUpdate = false;
	if(update) {
		out.push_back(m_Img[IMG_BACKGROUND_INDX]);
		out.push_back(m_Img[IMG_L2_INDX]);
		out.push_back(m_Text[TEXT_HELLO_INDX]);
		out.push_back(m_Text[TEXT_2_INDX]);
		out.push_back(m_Text[TEXT_3_INDX]);
		out.push_back(m_Text[TEXT_DYNAMIC_INDX]);
	}
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::initImgs() {
	std::for_each(&m_Img[0], &m_Img[IMG_ARRAY_SIZE], [](DrawParams_t & e){
			e.m_WidgetType = WidgetType_t::IMAGE;
		}
	);
	m_Img[IMG_BACKGROUND_INDX].m_ResrId = ResurcesId::IDLE_IMG;
	m_Img[IMG_L2_INDX].m_ResrId = ResurcesId::L2_IMG;
	if(!loadImgDimention()) {
		std::cerr << "Game::initImgs::loadImgDimention() failed." << std::endl;
		return false;
	}
	return true;
}

bool Game::loadImgDimention() {
	for(auto &e : m_Img) {
		auto img = m_ImageContainerIF->get(e.m_ResrId);
		if(nullptr == img) {
			std::cerr << "Game::ImageContainer::get() can't found id: " << e.m_ResrId << std::endl;
			return false;
		}
		auto rect = Rectangle(0, 0, img->m_W, img->m_H);
		e.m_DstRect = rect;
		e.m_SrcRect = rect;
	}
	return true;
}

bool Game::createTexts() {
	std::for_each(&m_Text[0], &m_Text[TEXT_ARRAY_SIZE], [](DrawParams_t & e){
			e.m_WidgetType = WidgetType_t::TEXT;
		}
	);
	if(!m_TextContainerIF->createText("Hello world!", Colors::GREEN, ResurcesId::ANGELINE_VINTAGE_160_TTF, m_Text[TEXT_HELLO_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->createText() fault"<< std::endl;
		return false;
	}
	if(!m_TextContainerIF->createText("Hello world!!", Colors::BLUE, ResurcesId::ANGELINE_VINTAGE_80_TTF, m_Text[TEXT_2_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->createText() fault"<< std::endl;
		return false;
	}
	if(!m_TextContainerIF->createText("Hello world!!!", Colors::RED, ResurcesId::ANGELINE_VINTAGE_40_TTF, m_Text[TEXT_3_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->createText() fault"<< std::endl;
		return false;
	}
	if(!m_TextContainerIF->createText("0h", Colors::ORANGE, ResurcesId::ANGELINE_VINTAGE_80_TTF, m_Text[TEXT_DYNAMIC_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->createText() fault"<< std::endl;
		return false;
	}
#if 0
	// test first free container
	if(!m_TextContainerIF->unloadText(m_Text[TEXT_HELLO_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->unloadText() fault"<< std::endl;
		return false;
	}
	if(!m_TextContainerIF->createText("Hello world!", Colors::GREEN, ResurcesId::ANGELINE_VINTAGE_160_TTF, m_Text[TEXT_HELLO_INDX].m_ResrId)) {
		std::cerr << "Game::createTexts::m_TextContainerIF->createText() fault"<< std::endl;
		return false;
	}
#endif
	for(auto &e : m_Text) {
		auto txt = m_TextContainerIF->get(e.m_ResrId);
		if(nullptr == txt) {
			std::cerr << "Game::createTexts::TextContainer::get() can't found id: " << e.m_ResrId << std::endl;
			return false;
		}
		e.m_DstRect = Rectangle(0, 0, txt->m_W, txt->m_H);
		e.m_SrcRect = Rectangle::UNDEFINED;
	}
	m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_X = 500;
	m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_Pos.m_Y = 250;
	return true;
}


bool Game::exitRequest() const {
	return !!(GameConfig::KEY_EXIT_MASK & m_KeysMask);
}

void Game::setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

bool Game::updateDynamicText(bool &update) {
	if(m_KeysMaskHold != m_KeysMask) {
		m_KeysMaskHold = m_KeysMask;
		std::ostringstream stream_txt;
		stream_txt << std::hex << m_KeysMask << "h" ;
		stream_txt.flush();
		if(!m_TextContainerIF->reloadText(stream_txt.str(),
				Colors::ORANGE, ResurcesId::ANGELINE_VINTAGE_80_TTF,
				m_Text[TEXT_DYNAMIC_INDX].m_ResrId)) {
			return false;
		}
		auto obj = m_TextContainerIF->get(m_Text[TEXT_DYNAMIC_INDX].m_ResrId);
		if(nullptr == obj) {
			std::cerr << "Game::TextContainer::get() can't found id: " << m_Text[TEXT_DYNAMIC_INDX].m_ResrId << std::endl;
			return false;
		}
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_H = obj->m_H;
		m_Text[TEXT_DYNAMIC_INDX].m_DstRect.m_W = obj->m_W;
		update = true;
	}
	return true;
}
