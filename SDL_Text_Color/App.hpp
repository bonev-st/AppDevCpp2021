/*
 * App.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <cstdint>

#include "utils/NoCopy.hpp"

#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/InputEvent.hpp"
#include "sdl_utils/Renderer.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"

#include "game/Game.hpp"

struct AppConfig;

class App : private NoCopy {
public:
	bool init(const AppConfig& cfg);
	bool start();

private:
	SDLLoader m_Loader;
	InputEvent m_InputEvents;
	Renderer m_Renderer;
	ImageContainer m_ImageContainer;
	TextContainer m_TextContainer;
	Game m_Game;
	std::shared_ptr<Texture::Texture_t>  m_Text;

	bool mainLoop();
	bool drawFrame();
	bool processFrame();

	void limitFPS(int64_t elapsed_us);

	void load_text();
	void show_text();

	bool drawImage(DrawParams_t & img);
	bool drawText(DrawParams_t & text);

};

#endif /* APP_HPP_ */
