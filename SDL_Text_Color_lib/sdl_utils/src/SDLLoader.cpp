/*
 * SDLLoader.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */
#include "sdl_utils/SDLLoader.hpp"

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "sdl_utils/SDLHelper.hpp"

bool SDLLoader::init() {
	bool rc = false;
	do {
        if(EXIT_SUCCESS != SDL_Init(SDL_INIT_EVERYTHING)) {
        	SDLHelper::print_SDL_Error("SDLLoader::init::SDL_Init() failed.");
        	break;
        }
        if(EXIT_SUCCESS != TTF_Init()) {
        	SDLHelper::print_SDL_Error("SDLLoader::init::TTF_Init() failed.");
        	break;
        }
		constexpr std::int32_t imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
        	SDLHelper::print_IMG_Error("SDLLoader::init::IMG_Init() failed.");
        	break;
		}
		if (0 > Mix_OpenAudio(44100					//sound frequency
							, MIX_DEFAULT_FORMAT	//sample format
							, 2						//stereo hardware channels
							, 2048)					//chunk size
			) {
        	SDLHelper::print_SDL_Error("SDLLoader::init::Mix_OpenAudio() failed.");
        	break;
		}
		rc = true;
	} while(0);
	return rc;
}

void SDLLoader::deinit() {
	while(Mix_Init(0)) {
	    Mix_Quit();
	}
	IMG_Quit();
	if(TTF_WasInit()) {
		TTF_Quit();
	}
	SDL_Quit();
}
