/*
 * ProcessorIF.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_PROCESSORIF_HPP_
#define GAME_GAMEPLAY_PROCESSORIF_HPP_

#include <vector>
#include <deque>

class Widget;

class ProcessorIF {
public:
	virtual ~ProcessorIF() = default;
	virtual std::vector<const Widget*> operator ()(const Widget* obj, const std::deque<const Widget *> & others) const = 0;

};


#endif /* GAME_GAMEPLAY_PROCESSORIF_HPP_ */
