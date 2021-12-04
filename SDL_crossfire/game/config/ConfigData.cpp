/*
 * ConfigData.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#include "game/config/ConfigData.hpp"

#include <iostream>

#include "game/config/Layout.hpp"
#include "game/config/GameConfigDef.hpp"
#include "game/config/GameConfig.hpp"

namespace ConfigData {

bool configImage(const GameConfig::ImgRes_t & cfg, GameConfig::ImgIndx_t cfg_id, std::size_t & out_img_id, const AbsCoordinates::ImgCfg_t * & out_config) {
	const auto it = cfg.find(cfg_id);
	if(cfg.end() == it) {
		std::cerr << "Can't find configuration of " << cfg_id << std::endl;
		return false;
	}
	out_img_id = it->second;
	out_config = Layout::getImgData(cfg_id);
	if(nullptr == out_config) {
		std::cerr << "Can't find Layout configuration of " << cfg_id << std::endl;
		return false;
	}
	return true;
}

bool configText(const GameConfig::TextRes_t & cfg, GameConfig::TextIndx_t cfg_id, std::size_t & out_font_id, const AbsCoordinates::TextCfg_t * & out_config) {
	const auto it = cfg.find(cfg_id);
	if(cfg.end() == it) {
		std::cerr << "Can't find configuration of " << cfg_id << std::endl;
		return false;
	}

	out_font_id = it->second;
	out_config = Layout::getTextData(cfg_id);
	if(nullptr == out_config) {
		std::cerr << "Can't find Layout configuration of " << cfg_id << std::endl;
		return false;
	}
	return true;
}

} /* namespace ConfigData */
