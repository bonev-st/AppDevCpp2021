/*
 * EnemyContainer.cpp
 *
 *  Created on: Dec 2, 2021
 *      Author: stanimir
 */

#include "game/widgets/EnemyContainer.hpp"

#include <iostream>
#include <algorithm>

#include "game/config/Layout.hpp"
#include "game/widgets/Ship.hpp"

bool EnemyContainer::init(const std::vector<std::size_t> & ship_img_id, double scale_factor, const std::vector<Point> & pos, uint32_t grid_size) {
	if(ship_img_id.empty()) {
		std::cerr << "Invalid image id container" << std::endl;
		return false;
	}
	if(pos.empty()) {
		std::cerr << "Invalid relative points container" << std::endl;
		return false;
	}
	m_Scale = scale_factor;
	m_GridSize = grid_size;
	m_ImgId = ship_img_id;
	const auto img_id = m_ImgId[0];
	m_Pos = pos;
	auto it_pos =  m_Pos.begin();

	m_EnemyContainer.resize(m_Pos.size());
	std::size_t ship_id = 1;
	for(auto & e: m_EnemyContainer) {
		e = std::make_shared<Ship>();
		if(!e->init(img_id, m_Scale, *it_pos, m_GridSize, ship_id)) {
			return false;
		}
		++it_pos;
		++ship_id;
	}
	m_Life.resize(m_Pos.size());
	std::fill(m_Life.begin(), m_Life.end(), 1);
	return true;
}

bool EnemyContainer::init_bullet(std::size_t bullet_img_id, double scale_factor, const Rectangle & field) {
	for(auto & e: m_EnemyContainer) {
		if(!e->init_bullet(bullet_img_id, scale_factor, field)) {
			return false;
		}
		e->reload(-1);
	}
	return true;
}

void EnemyContainer::setShipSpeed(double speed) {
	m_Speed = speed;
	for(auto & e: m_EnemyContainer) {
		e->setShipSpeed(m_Speed);
	}
}

void EnemyContainer::setBulledSpeed(double speed) {
	m_BulletsSpeed = speed;
	for(auto & e: m_EnemyContainer) {
		e->setBulletsSpeed(m_BulletsSpeed);
	}
}

void EnemyContainer::setReloadTime(uint32_t dly) {
	m_ReladTime = dly;
	for(auto & e: m_EnemyContainer) {
		e->reloadTime(m_ReladTime);
	}
}

bool EnemyContainer::event(const Action_t action, EnemyId_t id) {
	m_EnemyContainer[static_cast<std::size_t>(id)]->event(action);
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

void EnemyContainer::reset() {
	std::fill(m_Life.begin(), m_Life.end(), 1);
	for(std::size_t indx = 0; m_EnemyContainer.size() > indx; ++indx) {
		auto & e = m_EnemyContainer[indx];
		if(!e->init(m_ImgId[0], m_Scale, m_Pos[indx], m_GridSize, indx+1)) {
			std::cerr << "Enemy ship init failed" << std::endl;
		}
		e->reset();
	}
}

void EnemyContainer::reset(Widget * widget) {
	for(std::size_t indx = 0; m_EnemyContainer.size() > indx; ++indx) {
		auto & e = m_EnemyContainer[indx];
		if(e.get() == widget) {
			auto & life = m_Life[indx];
			if(m_ImgId.size() > life) {
				if(!e->init(m_ImgId[life], m_Scale, m_Pos[indx], m_GridSize, indx + 1)) {
					std::cerr << "Enemy ship init failed" << std::endl;
				}
				e->reset();
			}
			++life;
			return;
		}
	}
}

std::size_t EnemyContainer::getType(Widget * widget) const {
	for(std::size_t indx = 0; m_EnemyContainer.size() > indx; ++indx) {
		if(m_EnemyContainer[indx].get() == widget) {
			return m_Life[indx];
		}
	}
	return m_ImgId.size();
}

std::vector<Widget *> EnemyContainer::get() {
	std::vector<Widget *> rc;
	rc.reserve(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB));
	for(auto & e: m_EnemyContainer) {
		if(e->isDestroy() || !e->getVisible()) {
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

bool EnemyContainer::isKilled() const {
	bool rc = true;
	const auto max_life = m_ImgId.size();
	for(const auto e : m_Life) {
		if(max_life >= e) {
			rc = false;
			break;
		}
	}
	return rc;
}

