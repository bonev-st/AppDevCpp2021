#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <SDL.h>

SDL_Window* gWindow = nullptr;
SDL_Surface* globalScreenSurface = nullptr;
SDL_Surface* globalImage = nullptr;


int32_t init() {
    if(EXIT_SUCCESS != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    gWindow = SDL_CreateWindow("Hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); //use SDL_WINDOW_SHOWN as flags
    if(nullptr == gWindow) {
        std::cerr << "SDL_CreateWindow failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    globalScreenSurface = SDL_GetWindowSurface(gWindow);
    if(nullptr == globalScreenSurface) {
        std::cerr << "SDL_CreateWindow failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int32_t deinit() {
    if(globalImage) {
        SDL_FreeSurface(globalImage);
        globalImage = nullptr;
    }
    if(gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}

int32_t loadResources() {
    const std::string file_name = "resources/hello.bmp";
    globalImage = SDL_LoadBMP(file_name.c_str());
    if(nullptr == globalImage) {
        std::cerr << "SDL_LoadBMP failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int32_t draw() {
    if(EXIT_SUCCESS != SDL_BlitSurface(globalImage, &globalImage->clip_rect, globalScreenSurface, &globalScreenSurface->clip_rect)) {
        std::cerr << "SDL_BlitSurface failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if(EXIT_SUCCESS != SDL_UpdateWindowSurface(gWindow)) {
        std::cerr << "SDL_UpdateWindowSurface failed. Reason" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    SDL_Delay(3000);
    return EXIT_SUCCESS;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
    if(EXIT_SUCCESS != init()) {
        std::cerr << "init failed." << std::endl;
        return EXIT_FAILURE;
    }
    do {
        if(EXIT_SUCCESS != loadResources()) {
            std::cerr << "loadResources failed." << std::endl;
            break;
        }

        if(EXIT_SUCCESS != draw()) {
            std::cerr << "deinit failed." << std::endl;
            break;
        }
    } while(0);
    if(EXIT_SUCCESS != deinit()) {
        std::cerr << "deinit failed." << std::endl;
        return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
