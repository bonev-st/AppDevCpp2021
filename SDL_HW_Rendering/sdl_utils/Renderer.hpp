/*
 * Renderer.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_RENDERER_HPP_
#define SDL_UTILS_RENDERER_HPP_

#include <cstdint>
#include <memory>

#include "utils/NoCopy.hpp"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;
class Rectangle;

class Renderer : private NoCopy {
public:
	Renderer() = default;
	~Renderer() = default;

	int32_t init(SDL_Window *p_window);
	int32_t clearScreen();
	void finishFrame();
	int32_t copy(SDL_Texture *p_texture, const Rectangle &src_rec, const Rectangle &dst_rec);
	std::shared_ptr<SDL_Renderer> get() const {
		return m_Renderer;
	}

private:
	std::shared_ptr<SDL_Renderer> m_Renderer;
};

#endif /* SDL_UTILS_RENDERER_HPP_ */
