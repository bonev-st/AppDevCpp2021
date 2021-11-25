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

class Widget;
class ProcessorIF;

class CollisionDetect {
public:
	using Callback_t = std::function<void(const std::vector<const Widget*> &)>;

	bool init(const Widget* obj, const Callback_t & cb, ProcessorIF * proc);
	void add(const Widget & widged);
	bool remove(const Widget & widged);
	void processing();

private:
	Callback_t m_CB;
	std::deque<const Widget *> m_Continer;
	const Widget* m_Obj;
	ProcessorIF * m_Processor = nullptr;
};

#endif /* GAME_GAMEPLAY_COLLISIONDETECT_HPP_ */
