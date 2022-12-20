/*
 * Renderer.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_RENDERER_HPP_
#define SDL_UTILS_RENDERER_HPP_

#include <cstdint>

#include "utils/RAII_Handler.hpp"
#include "utils/NoCopy.hpp"

#include "sdl_utils/MainWindow.hpp"

struct SDL_Renderer;
struct SDL_Texture;
struct DrawParams_t;

class Renderer : private NoCopy {
public:
	bool init(const MainWindowCfg::Config_t &cfg);
	bool clearScreen() const;
	void finishFrame() const;
	bool copy(SDL_Texture *p_texture, const DrawParams_t & params) const;
	operator SDL_Renderer *() const;
	const DisplayMode::Mode_t & getDisplayMode() const;

private:
	MainWindow m_AppWindow;
	RAII_Handler<SDL_Renderer*, nullptr, std::function<void(SDL_Renderer*)>> m_Renderer;
};

#endif /* SDL_UTILS_RENDERER_HPP_ */
