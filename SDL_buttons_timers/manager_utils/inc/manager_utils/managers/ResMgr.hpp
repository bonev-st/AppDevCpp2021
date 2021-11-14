/*
 * ResMgr.hpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_RESMGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_RESMGR_HPP_

#include <string>

#include "utils/Singleton.hpp"

#include "manager_utils/managers/BaseMgr.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"

class SDL_Renderer;

namespace ResMgrConfig {
struct Config_t;
}
namespace Texture {
struct Texture_t;
}

class DrawParams_t;
class Color;
class TextContainer;

class ResMgr : public BaseMgr {
public:
	bool init(const ResMgrConfig::Config_t &cfg, SDL_Renderer* render, ImageContainer  *img, TextContainer* text);

	const Texture::Texture_t* get(const DrawParams_t & param) const;

	bool populateImg(DrawParams_t & param);
	bool createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param);
	bool releaseText(DrawParams_t & param);

private:
	SDL_Renderer* m_Rerender = nullptr;
	ImageContainer* m_ImageContainer = nullptr;
	TextContainer* m_TextContainer = nullptr;

	void setDimention(DrawParams_t & param, int32_t w, int32_t h, const ImageContainer::Frames_t * frames = nullptr);
};

using ResMgrInst = Singleton<ResMgr>;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_RESMGR_HPP_ */
