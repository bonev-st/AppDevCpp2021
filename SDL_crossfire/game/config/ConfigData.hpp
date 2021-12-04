/*
 * ConfigData.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_CONFIGDATA_HPP_
#define GAME_CONFIG_CONFIGDATA_HPP_

#include <cstdint>

#include "game/config/GameConfig.hpp"

namespace AbsCoordinates {
struct ImgCfg_t;
struct TextCfg_t;
}

namespace ConfigData {

bool configImage(const GameConfig::ImgRes_t & cfg, GameConfig::ImgIndx_t cfg_id, std::size_t & out_img_id, const AbsCoordinates::ImgCfg_t * & out_config);
bool configText(const GameConfig::TextRes_t & cfg, GameConfig::TextIndx_t cfg_id, std::size_t & out_font_id, const AbsCoordinates::TextCfg_t * & out_config);

} /* namespace ConfigData */

#endif /* GAME_CONFIG_CONFIGDATA_HPP_ */
