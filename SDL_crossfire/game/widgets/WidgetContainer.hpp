/*
 * TextureContainer.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_WIDGETCONTAINER_HPP_
#define GAME_WIDGETS_WIDGETCONTAINER_HPP_

#include <deque>
#include "manager_utils/drawing/RGB_Texture.hpp"

class Widget;

class WidgetContainer {
public:
	bool init(const Dimention& dimension, const Point & pos);
	void add(Widget * widget);
	bool remove(const Widget * widget);

	void draw();

private:
	bool m_Redraw = false;
	RGB_Texture m_Texture;
	std::deque<Widget * > m_Container;
};

#endif /* GAME_WIDGETS_WIDGETCONTAINER_HPP_ */
