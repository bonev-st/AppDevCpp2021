/*
 * Bonuses.hpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BONUSES_HPP_
#define GAME_WIDGETS_BONUSES_HPP_

#include <array>
#include "manager_utils/drawing/Image.hpp"
#include "manager_utils/drawing/Text.hpp"
#include "game/widgets/ScaleTexture.hpp"
#include "game/widgets/BlinkingAnimation.hpp"

enum class BonusId_t : uint8_t;

class Bonuses {
public:
	bool init(std::size_t img_id, double scale, const Point * ena_pos,
			const Point * dis_pos, std::size_t font_id, const Color & text_color);
	void reset();
	void enable(BonusId_t id);
	void disable();
	void hide(uint32_t points);
	void draw();

private:
	static constexpr std::size_t BONUS_NUMB = 4;
	static constexpr uint8_t ENABLE_NUMB = 12;
	static constexpr uint8_t DISABLE_NUMB = 6;
	static constexpr double ANIMATION_SPEED = 0.1;

	uint8_t m_Count = 0;
	uint8_t m_Current = BONUS_NUMB;

	BlinkingAnimation<Text> m_PointsText;
	ScaleTexture m_ScalePointsText;

	std::array<Point, BONUS_NUMB> m_EnablePointContaner;
	std::array<Point, BONUS_NUMB> m_DisablePointContaner;
	std::array<ScaleTexture, BONUS_NUMB> m_ScaleImgContaner;
	std::array<BlinkingAnimation<Image>, BONUS_NUMB> m_ImgContaner;
};

#endif /* GAME_WIDGETS_BONUSES_HPP_ */
