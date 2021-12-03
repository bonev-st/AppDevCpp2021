/*
 * EnemyContainer.cpp
 *
 *  Created on: Dec 2, 2021
 *      Author: stanimir
 */

#include "game/widgets/EnemyContainer.hpp"

#include <algorithm>

#include "game/config/Layout.hpp"
#include "game/widgets/Ship.hpp"

bool EnemyContainer::init(const std::vector<std::size_t> & ship_img_id, double scale_factor, const std::vector<Point> & pos, uint32_t grid_size) {
	const auto img_id = ship_img_id.front();
	m_Pos = pos;
	auto it_pos =  m_Pos.begin();

	m_EnemyContainer.resize(m_Pos.size());
	for(auto & e: m_EnemyContainer) {
		e = std::make_shared<Ship>();
		if(!e->init(img_id, scale_factor, *it_pos, grid_size)) {
			return false;
		}
		++it_pos;
	}
	return true;
}

bool EnemyContainer::init_bullet(std::size_t bullet_img_id, double scale_factor, int8_t max_bullets, uint32_t reload_time, const Rectangle & field) {
	for(auto & e: m_EnemyContainer) {
		if(!e->init_bullet(bullet_img_id, scale_factor, max_bullets, reload_time, field)) {
			return false;
		}
		e->reload(-1);
	}
	return true;
}

void EnemyContainer::setShipSpeed(double speed) {
	m_Speed = speed;
}

void EnemyContainer::setBulledSpeed(double speed) {
	m_BulletsSpeed = speed;
}

bool EnemyContainer::event([[maybe_unused]]const Action_t action, [[maybe_unused]]uint8_t line_of_fire, [[maybe_unused]]const Rectangle & shooter_rect) {
	return true;
}

void EnemyContainer::destroy(const Widget * widget) {
	for(auto & e: m_EnemyContainer) {
		if(e.get() == widget) {
			e->destroy();
		}
	}
}

void EnemyContainer::tick() {
	for(auto & e: m_EnemyContainer) {
		e->tick();
	}
}

void EnemyContainer::draw() {
	for(auto & e: m_EnemyContainer) {
		e->draw();
	}
}

std::vector<Widget *> EnemyContainer::get() {
	std::vector<Widget *> rc;
	rc.reserve(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB));
	for(auto & e: m_EnemyContainer) {
		if(e->isDestroy()) {
			continue;
		}
		rc.push_back(e.get());
	}
	return rc;
}

std::vector<Widget *> EnemyContainer::getBullets() {
	std::vector<Widget *> rc;
	rc.reserve(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB)*3);
	for(auto & e: m_EnemyContainer) {
		auto bullets = e->getBullets();
		rc.insert(rc.end(), bullets.begin(), bullets.end());
	}
	return rc;
}
