/*
 * TextContainer.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_
#define SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_

#include <unordered_map>
#include <functional>

#include "sdl_utils/config/FontConfig.hpp"
#include "utils/RAII_Handler.hpp"

typedef struct _TTF_Font TTF_Font;

class FontContainer {
public:
	bool init(const FontConfig::FontRes_t & cfg);
	const TTF_Font* get(std::size_t id) const;

private:
	using FontHandler_t = RAII_Handler<TTF_Font*, nullptr,  std::function<void(TTF_Font*)>>;
	std::unordered_map<std::size_t, FontHandler_t> m_Container;
};

#endif /* SDL_UTILS_CONTAINERS_FONTCONTAINER_HPP_ */
