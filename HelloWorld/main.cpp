#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include <SDL.h>

SDL_Window  *gWindow 			 = nullptr;
SDL_Surface *globalScreenSurface = nullptr;
SDL_Surface *globalImage 		 = nullptr;

static void show_SDL_Error(const std::string &info) {
    std::cerr << info << " Reason: " << SDL_GetError() << std::endl;
}

static int32_t init() {
    if(EXIT_SUCCESS != SDL_Init(SDL_INIT_VIDEO)) {
    	show_SDL_Error("SDL_Init() failed.");
        return EXIT_FAILURE;
    }
    gWindow = SDL_CreateWindow("Hello world"
    		, SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED
			, 640, 480
			, SDL_WINDOW_SHOWN);
    if(nullptr == gWindow) {
    	show_SDL_Error("SDL_CreateWindow() failed.");
        return EXIT_FAILURE;
    }
    globalScreenSurface = SDL_GetWindowSurface(gWindow);
    if(nullptr == globalScreenSurface) {
    	show_SDL_Error("SDL_GetWindowSurface() failed.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static void deinit() {
    if(globalImage) {
        SDL_FreeSurface(globalImage);
        globalImage = nullptr;
    }
    if(gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }
    SDL_Quit();
}

static int32_t loadResources() {
    const std::string file_name = "resources/hello.bmp";
    globalImage = SDL_LoadBMP(file_name.c_str());
    if(nullptr == globalImage) {
    	show_SDL_Error("SDL_LoadBMP() failed.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int32_t draw() {
    if(EXIT_SUCCESS != SDL_BlitSurface(globalImage, &globalImage->clip_rect, globalScreenSurface, &globalScreenSurface->clip_rect)) {
    	show_SDL_Error("SDL_BlitSurface() failed.");
        return EXIT_FAILURE;
    }
    if(EXIT_SUCCESS != SDL_UpdateWindowSurface(gWindow)) {
    	show_SDL_Error("SDL_UpdateWindowSurface() failed.");
        return EXIT_FAILURE;
    }
    SDL_Delay(3000);
    return EXIT_SUCCESS;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
    if(EXIT_SUCCESS != init()) {
        std::cerr << "init() failed." << std::endl;
        return EXIT_FAILURE;
    }
    do {
        if(EXIT_SUCCESS != loadResources()) {
            std::cerr << "loadResources() failed." << std::endl;
            break;
        }
        if(EXIT_SUCCESS != draw()) {
            std::cerr << "draw() failed." << std::endl;
            break;
        }
    } while(0);
    deinit();
	return EXIT_SUCCESS;
}
