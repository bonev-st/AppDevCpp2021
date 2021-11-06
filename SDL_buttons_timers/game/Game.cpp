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

#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

bool Game::init(const GameConfig::Config_t & cfg) {
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
		return false;
	}
	if(!m_Hero.init(ResurcesId::RUNNING_GIRL_SMALL_IMG)) {
		std::cerr << "m_Hero.init() failed." << std::endl;
		return false;
	}
	if(!m_Wheel.init(ResurcesId::WHEEL_IMG)) {
		std::cerr << "m_Wheel.init() failed." << std::endl;
		return false;
	}
	if(!createTexts()) {
		std::cerr << "Game:::init.createTexts() failed." << std::endl;
		return false;
	}
	if(!initButtons()) {
		std::cerr << "Game:::init.initButtons() failed." << std::endl;
		return false;
	}

	return true;
}

bool Game::events(const InputEvent & event, bool & exit) {
	m_RadioButtonStart.handleEvent(event);
	m_RadioButtonStartHidden.handleEvent(event);
	m_RadioButtonStop.handleEvent(event);
	m_RadioButtonStopDisabled.handleEvent(event);
	m_ButtonStart.handleEvent(event);
	m_ButtonStopDisabled.handleEvent(event);
	m_ToggleButtonStart.handleEvent(event);
	m_ToggleButtonStopDisabled.handleEvent(event);
	m_Wheel.handleEvent(event);
	m_Hero.handleEvent(event);

	const auto it = m_Keys.find(event.m_Key);
	if(m_Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return true;
}

bool Game::draw() const {
	m_Wheel.draw();
	m_Hero.draw();
	m_RadioButtonStart.draw();
	m_RadioButtonStartHidden.draw();
	m_RadioButtonStop.draw();
	m_RadioButtonStopDisabled.draw();
	m_ButtonStart.draw();
	m_ButtonStopDisabled.draw();
	m_ToggleButtonStart.draw();
	m_ToggleButtonStopDisabled.draw();
	m_Text[TEXT_BUTTON_INDX].draw();
	return true;
}

bool Game::process() {
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::createTexts() {
	if(!m_Text[TEXT_BUTTON_INDX].create(" ", Colors::GREEN, ResurcesId::ANGELINE_VINTAGE_40_TTF, Point(50,670))) {
		std::cerr << "Game::createTexts.m_Text[TEXT_BUTTON_INDX].create() fault"<< std::endl;
		return false;
	}
	return true;
}

bool Game::initButtons() {
	Point p = Point(800, 10);
	if(!m_RadioButtonStart.create(BTN_RADIO_START_INDX, ResurcesId::BUTTON_START_IMG, p)) {
		std::cerr << "Game::init.m_RadioButtonStart.init() failed." << std::endl;
		return false;
	}
	p.m_Y += 60;
	if(!m_RadioButtonStop.create(BTN_RADIO_STOP_INDX, ResurcesId::BUTTON_STOP_IMG, p)) {
		std::cerr << "Game::init.m_RadioButtonStop.init() failed." << std::endl;
		return false;
	}
	p.m_Y += 60;
	if(!m_RadioButtonStartHidden.create(BTN_RADIO_START_HIDDEN_INDX, ResurcesId::BUTTON_START_IMG, p)) {
		std::cerr << "Game::init.m_RadioButtonStartHidden.init() failed." << std::endl;
		return false;
	}
	m_RadioButtonStartHidden.setVisible(false);
	p.m_Y += 60;
	if(!m_RadioButtonStopDisabled.create(BTN_RADIO_STOP_DISABLED_INDX, ResurcesId::BUTTON_STOP_IMG, p)) {
		std::cerr << "Game::init.m_RadioButtonStop.init() failed." << std::endl;
		return false;
	}
	m_RadioButtonStopDisabled.setState(InputStates_t::DISABLED);
	m_ButtonCB = std::bind(&Game::buttonHandler, this, std::placeholders::_1);
	m_RadioGroup.init(&m_ButtonCB);

	m_RadioGroup.add(&m_RadioButtonStopDisabled);
	m_RadioGroup.add(&m_RadioButtonStart);
	m_RadioGroup.add(&m_RadioButtonStartHidden);
	m_RadioGroup.add(&m_RadioButtonStop);

	p.m_Y += 100;
	if(!m_ButtonStart.create(BTN_START_INDX, ResurcesId::BUTTON_START_IMG, p)) {
		std::cerr << "Game::init.m_ButtonStart.init() failed." << std::endl;
		return false;
	}
	m_ButtonStart.attachCB(&m_ButtonCB);
	p.m_Y += 60;
	if(!m_ButtonStopDisabled.create(BTN_STOP_DISABLED_INDX, ResurcesId::BUTTON_STOP_IMG, p)) {
		std::cerr << "Game::init.m_ButtonStopDisabled.init() failed." << std::endl;
		return false;
	}
	m_ButtonStopDisabled.setState(InputStates_t::DISABLED);
	m_ButtonStopDisabled.attachCB(&m_ButtonCB);

	m_ToggleButtonCB = std::bind(&Game::toggleButtonHandler, this, std::placeholders::_1, std::placeholders::_2);
	p.m_Y += 100;
	if(!m_ToggleButtonStart.create(BTN_TOGGLE_START_INDX, ResurcesId::BUTTON_START_IMG, p)) {
		std::cerr << "Game::init.m_ToggleButtonStart.init() failed." << std::endl;
		return false;
	}
	m_ToggleButtonStart.attachCB(&m_ToggleButtonCB);
	p.m_Y += 60;
	if(!m_ToggleButtonStopDisabled.create(BTN_TOGGLE_STOP_DISABLED_INDX, ResurcesId::BUTTON_STOP_IMG, p)) {
		std::cerr << "Game::init.m_ToggleButtonStopDisabled.init() failed." << std::endl;
		return false;
	}
	//m_ToggleButtonStopDisabled.setState(InputStates_t::DISABLED);
	m_ToggleButtonStopDisabled.attachCB(&m_ToggleButtonCB);

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

void Game::buttonHandler(std::size_t id) {
	switch(id) {
	case BTN_RADIO_START_INDX:
		if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::GREEN)) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
		}
		if(!m_Text[TEXT_BUTTON_INDX].setText("Radio Button START pressed")) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
		}
		m_Wheel.startAnimation();
		break;
	case BTN_RADIO_STOP_INDX:
		if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::GREEN)) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
		}
		if(!m_Text[TEXT_BUTTON_INDX].setText("Radio Button STOP pressed")) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
		}
		m_Wheel.stopAnimation();
		break;
	case BTN_RADIO_STOP_DISABLED_INDX:
		if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
		}
		if(!m_Text[TEXT_BUTTON_INDX].setText("Fault: Radio Button STOP disabled pressed")) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
		}
		break;
	case BTN_RADIO_START_HIDDEN_INDX:
		if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
		}
		if(!m_Text[TEXT_BUTTON_INDX].setText("Fault: Radio Button START hidden pressed")) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
		}
		break;
	case BTN_START_INDX:
		{
			if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::GREEN)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
			}
			std::string text = "Button START pressed ";
			text += std::to_string(++StartPressCounter);
			if(!m_Text[TEXT_BUTTON_INDX].setText(text)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
			}
			break;
		}
	case BTN_STOP_DISABLED_INDX:
		if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
		}
		if(!m_Text[TEXT_BUTTON_INDX].setText("Fault: Button STOP disabled  pressed")) {
			std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
		}
		break;
	default:
		{
			std::string txt {"Fault: Unknown button id: "};
			txt += std::to_string(id);
			if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
			}
			if(!m_Text[TEXT_BUTTON_INDX].setText(txt)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
			}
		}
	}
}

void Game::toggleButtonHandler(std::size_t id, bool state) {
	switch(id) {
	case BTN_TOGGLE_START_INDX:
		{
			std::string txt {"Toggle Button START "};
			txt += state?"pressed":"released";
			if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::GREEN)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
			}
			if(!m_Text[TEXT_BUTTON_INDX].setText(txt)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
			}
		}
		break;
	case BTN_TOGGLE_STOP_DISABLED_INDX:
		{
			std::string txt {"Fault: Toggle Button STOP disabled "};
			txt += state?"pressed":"released";
			if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
			}
			if(!m_Text[TEXT_BUTTON_INDX].setText(txt)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
			}
		}
		break;
	default:
		{
			std::string txt {"Fault: Unknown button id: "};
			txt += std::to_string(id);
			if(!m_Text[TEXT_BUTTON_INDX].setColor(Colors::RED)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setColor failed" << std::endl;
			}
			if(!m_Text[TEXT_BUTTON_INDX].setText(txt)) {
				std::cerr << "Game::buttonHandler.m_Text[TEXT_BUTTON_INDX].setText failed" << std::endl;
			}
		}
	}
}
