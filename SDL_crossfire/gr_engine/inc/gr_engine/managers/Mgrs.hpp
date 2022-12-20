/*
 * Mgr.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_MANAGERS_MGRS_HPP_
#define GR_ENGINE_INC_GR_ENGINE_MANAGERS_MGRS_HPP_

#include <array>

#include "gr_engine/config/ResourcesConfig.hpp"
#include "gr_engine/managers/BaseMgr.hpp"
#include "sdl_utils/Renderer.hpp"

#include "utils/inputs/InputEventIF.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"
#include "sdl_utils/containers/TextureContainer.hpp"
#include "sdl_utils/Renderer.hpp"

class Mgrs : public BaseMgr, public InputEventIF {
public:
	bool init(const ResourcesConfig::Config_t &cfg, DisplayMode::Mode_t & out_display_mode);
	std::size_t getActive() const final;
	std::size_t getMaxActive() const final;
	bool handleEvent(const InputEvent &e) final;

private:
	Renderer m_Renderer;
	ImageContainer m_ImageContainer;
	TextContainer m_TextContainer;
	TextureContainer m_TextureContainer;
	std::array<BaseMgr *, ManagersId_t::MGR_NUMB> m_Managers;
};

#endif /* GR_ENGINE_INC_GR_ENGINE_MANAGERS_MGRS_HPP_ */
