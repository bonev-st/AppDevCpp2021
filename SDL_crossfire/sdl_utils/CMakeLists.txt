cmake_minimum_required(VERSION 3.5.1)

project(sdl_utils LANGUAGES CXX)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(_INC_DIR ${_BASE_DIR}/sdl_utils)

#generate project library
add_library(
	${PROJECT_NAME} STATIC
		${_INC_DIR}/config/ImgConfig.hpp
		${_INC_DIR}/config/FontConfig.hpp
		${_INC_DIR}/containers/ImageContainer.hpp
		${_INC_DIR}/containers/FontContainer.hpp
		${_INC_DIR}/containers/TextContainer.hpp
		${_INC_DIR}/containers/TextureContainer.hpp
		${_INC_DIR}/InputEvent.hpp
		${_INC_DIR}/MainWindow.hpp
		${_INC_DIR}/Renderer.hpp
		${_INC_DIR}/SDLHelper.hpp
		${_INC_DIR}/SDLLoader.hpp
		${_INC_DIR}/Texture.hpp
		${_INC_DIR}/Timer.hpp
	
		${_SRC_DIR}/containers/ImageContainer.cpp
		${_SRC_DIR}/containers/FontContainer.cpp
		${_SRC_DIR}/containers/TextContainer.cpp
		${_SRC_DIR}/containers/TextureContainer.cpp
		${_SRC_DIR}/InputEvent.cpp
		${_SRC_DIR}/MainWindow.cpp
		${_SRC_DIR}/Renderer.cpp
		${_SRC_DIR}/SDLHelper.cpp
		${_SRC_DIR}/SDLLoader.cpp
		${_SRC_DIR}/Texture.cpp
		${_SRC_DIR}/Timer.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}                                                                           
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules
)

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../utils utils)

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
        PUBLIC
            ${_BASE_DIR}
        PRIVATE
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
        	utils
        PRIVATE
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARY}
            ${SDL2_TTF_LIBRARY}
            ${SDL2_MIXER_LIBRARY}
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
message("Debug build")
	target_compile_definitions(
		${PROJECT_NAME}
			PRIVATE
				-DSHOW_MEM_ALLOC_INFO=1
	)
endif()
