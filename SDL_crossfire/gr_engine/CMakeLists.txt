cmake_minimum_required(VERSION 3.5.1)

project(gr_engine LANGUAGES CXX)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(_INC_DIR ${_BASE_DIR}/gr_engine)

#generate project library
add_library(
	${PROJECT_NAME} STATIC
		${_INC_DIR}/config/DrawMgrConfig.hpp
		${_INC_DIR}/config/ResMgrConfig.hpp
		${_INC_DIR}/config/ResourcesConfig.hpp
		${_INC_DIR}/config/DebugCfg.hpp
		${_INC_DIR}/managers/ResMgr.hpp
		${_INC_DIR}/managers/BaseMgr.hpp
		${_INC_DIR}/managers/DrawMgr.hpp
		${_INC_DIR}/managers/Timer2Mgr.hpp
		${_INC_DIR}/managers/Mgrs.hpp		
		${_INC_DIR}/drawing/Widget.hpp
		${_INC_DIR}/drawing/Image.hpp
		${_INC_DIR}/drawing/Text.hpp
		${_INC_DIR}/drawing/RGB_Texture.hpp
		${_INC_DIR}/drawing/RGB_Texture.hpp
		${_INC_DIR}/input/ButtonBase.hpp
		${_INC_DIR}/input/RadioContainer.hpp
		${_INC_DIR}/input/RadioWidget.hpp
		${_INC_DIR}/timer/Timer2Client.hpp
		${_INC_DIR}/widgets/BlinkingAnimation.hpp
		${_INC_DIR}/widgets/SpriteAnimation.hpp
		${_INC_DIR}/widgets/RotateAnimation.hpp
		${_INC_DIR}/widgets/ScaleTexture.hpp
		${_INC_DIR}/widgets/WidgetContainer.hpp
		${_INC_DIR}/widgets/WidgetTO.hpp
		${_INC_DIR}/widgets/InitHelper.hpp

		${_SRC_DIR}/config/DebugCfg.cpp
		${_SRC_DIR}/managers/ResMgr.cpp
		${_SRC_DIR}/managers/DrawMgr.cpp
		${_SRC_DIR}/managers/Timer2Mgr.cpp
		${_SRC_DIR}/managers/Mgrs.cpp		
		${_SRC_DIR}/drawing/Widget.cpp
		${_SRC_DIR}/drawing/Image.cpp
		${_SRC_DIR}/drawing/Text.cpp
		${_SRC_DIR}/drawing/RGB_Texture.cpp		
		${_SRC_DIR}/input/ButtonBase.cpp
		${_SRC_DIR}/input/RadioContainer.cpp
		${_SRC_DIR}/timer/Timer2Client.cpp
		${_SRC_DIR}/widgets/ScaleTexture.cpp
		${_SRC_DIR}/widgets/WidgetContainer.cpp
		${_SRC_DIR}/widgets/InitHelper.cpp
		
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

if (MSVC)
set_target_cpp_standard(${PROJECT_NAME} 20)
else()
set_target_cpp_standard(${PROJECT_NAME} 17)
endif()
enable_target_warnings(${PROJECT_NAME})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../sdl_utils sdl_utils)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${_BASE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
        	sdl_utils
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
message("Debug build")
	target_compile_definitions(
		${PROJECT_NAME}
			PRIVATE
				-DSHOW_MEM_ALLOC_INFO=1
	)
endif()
