/*
 * GameListener.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMELISTENER_HPP_
#define GAME_GAMELISTENER_HPP_

#include <cstdint>

class GameListener {
public:
	virtual ~GameListener() = default;
	virtual void setPoints(std::uint32_t points);

};

#endif /* GAME_GAMELISTENER_HPP_ */
