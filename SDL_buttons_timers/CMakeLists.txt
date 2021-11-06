cmake_minimum_required(VERSION 3.5.1)

project(but_tim LANGUAGES CXX)

#generate project binary
add_executable(
	${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Hero.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Hero.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Button.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Button.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/RadioButton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/RadioButton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ToggleButton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ToggleButton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Wheel.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Wheel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfig.hpp
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

