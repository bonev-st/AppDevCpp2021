/*
 * App.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <cstdint>
#include <array>
#include <memory>

#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/MainWindow.hpp"
#include "sdl_utils/InputEvent.hpp"

class App {
public:
	App() = default;
	~App() = default;

	int32_t init();
	int32_t start();

private:
	typedef enum _KeyMask_t : std::uint32_t {
		KEY_UP_MASK 	= 1u << 0,
		KEY_DOWN_MASK 	= 1u << 1,
		KEY_LEFT_MASK 	= 1u << 2,
		KEY_RIGHT_MASK 	= 1u << 3,
	} KeyMask_t;

	typedef enum _ImgId_t {
		IDLE_IMG,
		UP_IMG,
		DOWN_IMG,
		LEFT_IMG,
		RIGHT_IMG,
		NUMB_IMG
	} ImgId_t;

	SDLLoader m_Loader;
	MainWindow m_AppWindow;
	std::array<std::shared_ptr<SDL_Surface>, NUMB_IMG> m_Image;
	InputEvent m_InputEvents;
	uint32_t m_KeysMask = 0;

	int32_t loadResources();

	int32_t mainLoop();
	int32_t drawFrame();
	int32_t processFrame();
	int32_t handleEvent();

	void limitFPS(int64_t elapsed_us);
	void setExitRequest();
	void setKeyRequest(bool pressed, KeyMask_t key_mask);
};

#endif /* APP_HPP_ */
