/*
 * TopLevel.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_TOPLEVEL_HPP_
#define GAME_WIDGETS_TOPLEVEL_HPP_

#include "game/widgets/FPS.hpp"
#include "game/widgets/Ship.hpp"
#include "game/widgets/Ammunition.hpp"
#include "game/widgets/Bonuses.hpp"
#include "game/widgets/Background.hpp"
#ifdef DEBUG
#include "game/widgets/GridPoint.hpp"
#endif
#include "game/widgets/ExplosionContainer.hpp"
#include "game/widgets/EnemyContainer.hpp"
#include "game/gameplay/CollitionMgr.hpp"

#include "game/config/GameConfig.hpp"

class InputEvent;

class TopLevel {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);
	void draw();

	bool processing();
	void tick();
	bool events(const InputEvent & event);
	const Widget & getShip() const;

private:
	GameConfig::KeyRes_t m_Keys;

	Ship m_Ship;
	EnemyContainer m_Enemies;
	Ammunition m_Ammunition;
	Bonuses m_Bonuses;
	ExplosionContainer m_ExplosionContainer;
	CollitionMgr m_CollitionMgr;
#ifdef DEBUG
	GridPoint m_GridPoint;
#endif

	bool initWidgets(const DisplayMode::Mode_t & display_mode, const GameConfig::ImgRes_t & cfg);
	bool setKeyRequest(GameConfig::KeyMask_t mask);

	void onShipFire(const Point &pos, int8_t rem);
	void onCB_Ammun(const std::vector<Widget *> &data);
	void onCB_Bonus(const std::vector<Widget *> &data);
	void onCB_Ship(const std::vector<Widget *> &data);
	void onCB_Enemy(const std::vector<Widget *> &data);
	void onCB_Ship2Ship(const std::vector<Widget *> &data);
	void onAnimation0(Widget * data);
};

#endif /* GAME_WIDGETS_TOPLEVEL_HPP_ */
