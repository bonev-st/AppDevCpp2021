/*
 * CollisionDetect.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_COLLISIONDETECT_HPP_
#define GAME_GAMEPLAY_COLLISIONDETECT_HPP_

#include <functional>
#include <deque>
#include <vector>

class Widget;
class ProcessorIF;

class CollisionDetect {
public:
	using Callback_t = std::function<void(const std::vector<const Widget*> &)>;

	bool init(const Callback_t & cb, ProcessorIF * proc);
	void setObj(const Widget * widget);
	void add(const Widget * widget);
	bool remove(const Widget * widget);
	void processing();

private:
	Callback_t m_CB;
	std::deque<const Widget *> m_Container;
	const Widget* m_Obj = nullptr;
	ProcessorIF * m_Processor = nullptr;
};

#endif /* GAME_GAMEPLAY_COLLISIONDETECT_HPP_ */
