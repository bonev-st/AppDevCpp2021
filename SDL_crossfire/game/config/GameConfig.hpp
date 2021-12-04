/*
 * GameConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMECONFIG_HPP_
#define GAME_GAMECONFIG_HPP_

#include <unordered_map>

namespace Keyboard {
enum Key : uint32_t;
}

namespace GameConfig {

enum KeyMask_t : std::uint32_t;
enum ImgIndx_t : uint32_t;
enum ImgIndx_t : uint32_t;
enum TextIndx_t : uint32_t;

using Key = Keyboard::Key;
using KeyRes_t = std::unordered_map<Key, KeyMask_t>;
using ImgRes_t = std::unordered_map<ImgIndx_t, std::size_t>;
using TextRes_t = std::unordered_map<TextIndx_t, std::size_t>;

struct Config_t {
	KeyRes_t m_Keys;
	ImgRes_t m_Img;
	TextRes_t m_Text;
};
}

#endif /* GAME_GAMECONFIG_HPP_ */
