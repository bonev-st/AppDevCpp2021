/*
 * CollisionDetect.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_COLLISIONDETECT_HPP_
#define GAME_GAMEPLAY_COLLISIONDETECT_HPP_

#include <functional>
#include <vector>

class Widget;
class ProcessorIF;

class CollisionDetect {
public:
	using Callback_t = std::function<void(const std::vector<Widget*> &)>;

	bool init(const Callback_t & cb, ProcessorIF * proc);
	void setObj(Widget * widget);
	void processing(std::vector<Widget*> container);

private:
	Callback_t m_CB;
	Widget* m_Obj = nullptr;
	ProcessorIF * m_Processor = nullptr;
};

#endif /* GAME_GAMEPLAY_COLLISIONDETECT_HPP_ */
