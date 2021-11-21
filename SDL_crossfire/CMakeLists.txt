cmake_minimum_required(VERSION 3.5.1)

project(crossfire LANGUAGES CXX)

#generate project binary
add_executable(
	${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/SpriteAnimation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/RotateAnimation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/FPS.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/FPS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ship.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/ActionDef.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/ActionBuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/ActionBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/UnitAction.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/UnitAction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfig.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/Layout.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/Layout.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/App.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfig.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfigLoader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfigLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/CommonDefines.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

#message("CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}") 

set_target_cpp_standard(${PROJECT_NAME} 17)

enable_target_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
        	manager_utils
)

add_subdirectory(manager_utils)

