/*
 * Mgr.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_

#include <array>

#include "sdl_utils/Renderer.hpp"

#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/managers/BaseMgr.hpp"
#include "manager_utils/config/ResourcesConfig.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"
#include "sdl_utils/Renderer.hpp"

class Mgrs : public BaseMgr, public InputEventIF {
public:
	bool init(const ResourcesConfig::Config_t &cfg);
	std::size_t getActive() const final;
	std::size_t getMaxActive() const final;
	bool handleEvent(const InputEvent &e) final;

private:
	Renderer m_Renderer;
	ImageContainer m_ImageContainer;
	TextContainer m_TextContainer;
	std::array<BaseMgr *, ManagersId_t::MGR_NUMB> m_Managers;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_ */
