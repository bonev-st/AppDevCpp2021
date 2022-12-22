/*
 * ResourceManager.hpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#ifndef UTILS_SRC_RESOURCE_MANAGER_RESOURCEMANAGER_HPP_
#define UTILS_SRC_RESOURCE_MANAGER_RESOURCEMANAGER_HPP_

#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"

struct SDL_Renderer;

class ResourceManager {
public:
	ResourceManager() = default;

	void init(SDL_Renderer* render);
	bool loadImg(const ImgConfig::ImgRes_t & cfg);
	bool loadFonts(const FontConfig::FontRes_t & cfg);

	const Texture::Texture_t* get(const DrawParams_t & param) const;
	bool populateImg(DrawParams_t & param);
	bool createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param);
	bool releaseText(DrawParams_t & param);

private:
	SDL_Renderer* m_Rerender = nullptr;
	ImageContainer m_ImageContainer;
	TextContainer m_TextContainer;

	void setDimention(DrawParams_t & param, int32_t w, int32_t h);
};

#endif /* UTILS_SRC_RESOURCE_MANAGER_RESOURCEMANAGER_HPP_ */
