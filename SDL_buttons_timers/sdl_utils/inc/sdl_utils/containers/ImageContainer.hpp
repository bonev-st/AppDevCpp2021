/*
 * ImageContainer.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_CONTAINERS_IMAGECONTAINER_HPP_
#define SDL_UTILS_CONTAINERS_IMAGECONTAINER_HPP_

#include <unordered_map>
#include <memory>
#include <vector>

#include "sdl_utils/config/ImgConfig.hpp"
#include "sdl_utils/Texture.hpp"

class ImageContainer {
public:
	using Frames_t = std::vector<Rectangle>;

	bool init(const ImgConfig::ImgRes_t & cfg, SDL_Renderer *p_renderer);
	const Texture::Texture_t* get(std::size_t id) const;
	const Frames_t* getFrames(std::size_t id) const;

private:
	std::unordered_map<std::size_t, std::shared_ptr<Texture::Texture_t>> m_Container;
	std::unordered_map<std::size_t, Frames_t> m_Frames;
};

#endif /* SDL_UTILS_CONTAINERS_IMAGECONTAINER_HPP_ */
