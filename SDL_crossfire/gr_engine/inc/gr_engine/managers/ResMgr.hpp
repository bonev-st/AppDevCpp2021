/*
 * ResMgr.hpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_MANAGERS_RESMGR_HPP_
#define GR_ENGINE_INC_GR_ENGINE_MANAGERS_RESMGR_HPP_

#include <string>

#include "gr_engine/managers/BaseMgr.hpp"
#include "utils/Singleton.hpp"

#include "sdl_utils/containers/ImageContainer.hpp"

class SDL_Renderer;

namespace ResMgrConfig {
struct Config_t;
}
namespace Texture {
struct Texture_t;
}
namespace DisplayMode {
struct Mode_t;
}

class DrawParams_t;
class Color;
class TextContainer;
class TextureContainer;

class ResMgr : public BaseMgr {
public:
	bool init(const ResMgrConfig::Config_t &cfg, SDL_Renderer* render,
			ImageContainer *img, TextContainer* text, TextureContainer *texture);

	const Texture::Texture_t* get(const DrawParams_t & param) const;
	bool release(DrawParams_t & param);

	bool populateImg(DrawParams_t & param);
	bool createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param);

	bool createTexture(const Dimention &dim, const Color & color, DrawParams_t & param);
	bool setTextureColor(const Color & color, DrawParams_t & param);
	std::shared_ptr<SDL_Texture> getTextureRenderLock(const DrawParams_t & param);

private:
	SDL_Renderer* m_Rerender = nullptr;
	ImageContainer* m_ImageContainer = nullptr;
	TextContainer* m_TextContainer = nullptr;
	TextureContainer* m_TextureContainer = nullptr;

	void setDimention(DrawParams_t & param, int32_t w, int32_t h, const ImageContainer::Frames_t * frames = nullptr);
};

using ResMgrInst = Singleton<ResMgr>;

#endif /* GR_ENGINE_INC_GR_ENGINE_MANAGERS_RESMGR_HPP_ */
