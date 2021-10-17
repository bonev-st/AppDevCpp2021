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

#include "sdl_utils/MainWindow.hpp"

#include "utils/NoCopy.hpp"

struct SDL_Renderer;
struct SDL_Texture;
class Rectangle;

class Renderer : private NoCopy {
public:
	int32_t init(const MainWindow::MainWindowCfg_t &cfg);
	int32_t clearScreen();
	void finishFrame();
	int32_t copy(SDL_Texture *p_texture, const Rectangle &src_rec, const Rectangle &dst_rec);
	SDL_Renderer* get() const {
		return m_Renderer.get();
	}

private:
	std::shared_ptr<MainWindow::MainWindow_t> m_AppWindow;
	std::shared_ptr<SDL_Renderer> m_Renderer;
};

#endif /* SDL_UTILS_RENDERER_HPP_ */
