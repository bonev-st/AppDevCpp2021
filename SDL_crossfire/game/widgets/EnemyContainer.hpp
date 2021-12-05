/*
 * EnemyContainer.hpp
 *
 *  Created on: Dec 2, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_ENEMYCONTAINER_HPP_
#define GAME_WIDGETS_ENEMYCONTAINER_HPP_

#include <memory>
#include <vector>

#include "gr_engine/drawing/Image.hpp"
#include "gr_engine/widgets/ScaleTexture.hpp"
#include "game/action/Action.hpp"

class Ship;
enum class EnemyId_t : uint8_t;

class EnemyContainer {
public:
	bool init(const std::vector<std::size_t> & ship_img_id, double scale_factor, const std::vector<Point> & pos, uint32_t grid_size);
	bool init_bullet(std::size_t bullet_img_id, double scale_factor, const Rectangle & field);
	void setShipSpeed(double speed);
	void setBulledSpeed(double speed);
	void setReloadTime(uint32_t dly);
	bool event(const Action_t action, EnemyId_t id);
	void destroy(const Widget * widget);
	void tick();
	void draw();
	void reset();
	void reset(Widget * widget);
	std::size_t getType(Widget * widget) const;

	std::vector<Widget *> get();
	std::vector<Widget *> getBullets();
	bool isKilled() const;

private:
	std::vector<std::size_t> m_ImgId;
	std::vector<std::size_t> m_Life;
	std::vector<Point> m_Pos;
	uint32_t m_GridSize = 0;
	double m_Speed = 0;
	double m_BulletsSpeed = 0;
	uint32_t m_ReladTime = 0;
	double m_Scale = 0;

	std::vector<std::shared_ptr<Ship>> m_EnemyContainer;
};

#endif /* GAME_WIDGETS_ENEMYCONTAINER_HPP_ */
