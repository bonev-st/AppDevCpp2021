/*
 * CD_ClientIF.hpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_CD_CLIENTIF_HPP_
#define GAME_GAMEPLAY_CD_CLIENTIF_HPP_

class CD_ClientIF {
public:
	virtual ~CD_ClientIF() = default;
	virtual void collision() = 0;
};

#endif /* GAME_GAMEPLAY_CD_CLIENTIF_HPP_ */
