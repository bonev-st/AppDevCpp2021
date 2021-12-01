/*
 * ExplosionContainer.hpp
 *
 *  Created on: Nov 29, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_EXPLOSIONCONTAINER_HPP_
#define GAME_WIDGETS_EXPLOSIONCONTAINER_HPP_

#include <functional>
#include <memory>

#include "utils/containers/FirstFreeContainer.hpp"

#include "manager_utils/drawing/Image.hpp"

#include "game/widgets/ScaleTexture.hpp"
#include "game/widgets/SpriteAnimation.hpp"

class ExplosionContainer {
public:
	using Callback_t = std::function<void(Widget*)>;

	bool init(std::size_t img_id, double scale);
	bool show(Widget * src, const Callback_t & cb);
	void draw();

private:
	struct Data_t {
		SpriteAnimation<Image> m_Img;
		ScaleTexture m_Scale;
		Callback_t m_CB;
		Widget * m_Widget = nullptr;
	};

	static constexpr uint32_t TIMER_PERIOD = 25;
	static constexpr std::size_t HIDE_FAME = 24;

	std::size_t m_ImgId = -1;
	double m_Scale = 1;
	FirstFreeContainer<std::shared_ptr<Data_t>> m_Container;

	void onAnimationTick(std::size_t frame, void * param);
};

#endif /* GAME_WIDGETS_EXPLOSIONCONTAINER_HPP_ */
