/*
 * TextContainer.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_
#define SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_

#include <unordered_map>
#include <memory>

#include "sdl_utils/config/FontConfig.hpp"

typedef struct _TTF_Font TTF_Font;

class FontContainer {
public:
	bool init(const FontConfig::FontRes_t & cfg);
	const TTF_Font* get(uint32_t id) const;

private:
	std::unordered_map<uint32_t, std::shared_ptr<TTF_Font>> m_Container;
};

#endif /* SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_ */
