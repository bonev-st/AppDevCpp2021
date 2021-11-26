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
namespace DiplayMode {
struct Mode_t;
}

class DrawParams_t;
class Color;
class TextContainer;
class TextureContainer;

class ResMgr : public BaseMgr {
public:
	bool init(const ResMgrConfig::Config_t &cfg, SDL_Renderer* render,
			ImageContainer *img, TextContainer* text, TextureContainer *texture,
			const DiplayMode::Mode_t & display_mode);

	const Texture::Texture_t* get(const DrawParams_t & param) const;

	bool populateImg(DrawParams_t & param);
	bool createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param);
	bool releaseText(DrawParams_t & param);

	bool createTexture(const Color & color, DrawParams_t & param);
	bool releaseTexture(DrawParams_t & param);
	std::shared_ptr<SDL_Texture> getTextureRenderLock(const DrawParams_t & param);

private:
	SDL_Renderer* m_Rerender = nullptr;
	ImageContainer* m_ImageContainer = nullptr;
	TextContainer* m_TextContainer = nullptr;
	TextureContainer* m_TextureContainer = nullptr;

	void setDimention(DrawParams_t & param, int32_t w, int32_t h, const ImageContainer::Frames_t * frames = nullptr);
};

using ResMgrInst = Singleton<ResMgr>;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_RESMGR_HPP_ */
