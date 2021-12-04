cmake_minimum_required(VERSION 3.5.1)

project(utils LANGUAGES CXX)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(_INC_DIR ${_BASE_DIR}/utils)

#generate project library
add_library(
	${PROJECT_NAME} STATIC
		${_INC_DIR}/NoCopy.hpp
		${_INC_DIR}/Destroy.hpp
		${_INC_DIR}/Singleton.hpp
		${_INC_DIR}/RAII_Handler.hpp
		${_INC_DIR}/containers/FirstFreeContainer.hpp
		${_INC_DIR}/drawing/MainWindowCfg.hpp
		${_INC_DIR}/drawing/DrawParams.hpp
		${_INC_DIR}/drawing/Dimention.hpp
		${_INC_DIR}/drawing/Point.hpp
		${_INC_DIR}/drawing/Rectangle.hpp
		${_INC_DIR}/drawing/Color.hpp
		${_INC_DIR}/drawing/BlendMode.hpp		
		${_INC_DIR}/drawing/FlipMode.hpp
		${_INC_DIR}/drawing/WidgetType.hpp
		${_INC_DIR}/drawing/DisplayMode.hpp
		${_INC_DIR}/inputs/EventDefines.h
		${_INC_DIR}/inputs/InputEventIF.hpp
		${_INC_DIR}/time/Time.hpp
		${_INC_DIR}/timer/Timer2Def.hpp
		${_INC_DIR}/thread/ThreadUtils.hpp
		${_INC_DIR}/geometry/Geometry.hpp
		${_INC_DIR}/Filter/ExpFilter.hpp
	
		${_SRC_DIR}/drawing/Point.cpp
		${_SRC_DIR}/drawing/Rectangle.cpp
		${_SRC_DIR}/drawing/Dimention.cpp
		${_SRC_DIR}/drawing/Color.cpp
		${_SRC_DIR}/thread/ThreadUtils.cpp		
		${_SRC_DIR}/time/Time.cpp
		${_SRC_DIR}/geometry/Geometry.cpp
		${_SRC_DIR}/Filter/ExpFilter.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${_BASE_DIR}
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
message("Debug build")
	target_compile_definitions(
		${PROJECT_NAME}
			PRIVATE
				-DSHOW_MEM_ALLOC_INFO=1
	)
endif()
