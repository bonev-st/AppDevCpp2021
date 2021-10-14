cmake_minimum_required(VERSION 3.5.1)

project(sdl_events LANGUAGES CXX)

#generate project binary
add_executable(
	${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/SDLHelper.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/SDLHelper.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/SDLLoader.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/SDLLoader.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/MainWindow.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/MainWindow.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/Texture.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/Texture.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/Timer.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/Timer.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/InputEvent.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/InputEvent.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/sdl_utils/Destroy.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/drawing/Point.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/drawing/Point.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/drawing/Rectangle.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/drawing/Rectangle.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/inputs/EventDefines.h		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/thread/ThreadUtils.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/thread/ThreadUtils.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/time/Time.hpp		
	${CMAKE_CURRENT_SOURCE_DIR}/utils/time/Time.cpp		
	${CMAKE_CURRENT_SOURCE_DIR}/App.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}                                                                           
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules
)

#message("CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}") 

set_target_cpp_standard(${PROJECT_NAME} 17)

enable_target_warnings(${PROJECT_NAME})

find_package(SDL2 REQUIRED)

if(UNIX)
    set(SDL2_image_name SDL2_image)
    set(SDL2_ttf_name SDL2_ttf)
    set(SDL2_mixer_name SDL2_mixer)
elseif(WIN32 OR APPLE)
    set(SDL2_image_name SDL2_IMAGE)
    set(SDL2_ttf_name SDL2_TTF)
    set(SDL2_mixer_name SDL2_MIXER)
endif()

find_package(${SDL2_image_name} REQUIRED)
find_package(${SDL2_ttf_name} REQUIRED)
find_package(${SDL2_mixer_name} REQUIRED)

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARY}
            ${SDL2_TTF_LIBRARY}
            ${SDL2_MIXER_LIBRARY}
)
