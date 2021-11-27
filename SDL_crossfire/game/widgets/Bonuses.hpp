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
#include "game/widgets/WidgetTO.hpp"

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
	static constexpr double ANIMATION_PERIOD = 500;
	static constexpr double TEXT_TO = 10000;

	struct Position_t {
		Point m_EnablePos;
		Point m_DisablePos;
	};
	struct BonusWidget_t {
		Image m_Img;
		BlinkingAnimation<ScaleTexture> m_Scaled;
	};
	struct Bonus_t {
		Position_t m_Position;
		BonusWidget_t m_Widget;
	};

	uint8_t m_Count = 0;
	uint8_t m_Current = BONUS_NUMB;

	std::array<Bonus_t, BONUS_NUMB> m_BonusContaner;
	Text m_PointsText;
	WidgetTO<ScaleTexture> m_ScalePointsText;

	void setEnable(std::size_t id);
	void setDisable(std::size_t id);
	void setHide(std::size_t id, uint32_t number);
};

#endif /* GAME_WIDGETS_BONUSES_HPP_ */
