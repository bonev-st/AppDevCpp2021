/*
 * TextureContainer.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_WIDGETS_WIDGETCONTAINER_HPP_
#define GR_ENGINE_WIDGETS_WIDGETCONTAINER_HPP_

#include <deque>

#include "gr_engine/drawing/RGB_Texture.hpp"
#include "gr_engine/timer/Timer2Client.hpp"

class Widget;

class WidgetContainer {
public:
	bool init(const Dimention& dimension, const Point & pos);
	void add(Widget * widget);
	bool remove(const Widget * widget);
	bool getVisible() const;
	void setVisible(bool val);

	void draw();

private:
	RGB_Texture m_Texture;
	std::deque<Widget * > m_Container;
	Timer2Client m_DebugTimer;

	bool resetTimer();
};

#endif /* GAME_WIDGETS_WIDGETCONTAINER_HPP_ */
