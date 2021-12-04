cmake_minimum_required(VERSION 3.5.1)

project(crossfire LANGUAGES CXX)

#generate project binary
add_executable(
	${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/SpriteAnimation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/RotateAnimation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/BlinkingAnimation.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/FPS.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/FPS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ship.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ship.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Bullets.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Bullets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ammunition.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Ammunition.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ScaleTexture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ScaleTexture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Bonuses.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Bonuses.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/WidgetTO.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/WidgetContainer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/WidgetContainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Background.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Background.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/GridPoint.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/GridPoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ExplosionContainer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/ExplosionContainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/EnemyContainer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/EnemyContainer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Level1.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Level1.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Level2.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/Level2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/InitHelper.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/widgets/InitHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/Action.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/Action.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/ActionBuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/ActionBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/UnitAction.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/UnitAction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/action/BulletAction.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/ProcessorIF.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CollisionDetect.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CollisionDetect.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CD_Through.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CD_Through.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CD_Touch.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CD_Touch.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CD_ClientIF.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/BulletsCtrl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/BulletsCtrl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CollitionMgr.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/gameplay/CollitionMgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfigDef.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfig.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/GameConfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/ConfigData.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/ConfigData.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/Layout.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/Layout.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/AbsCoordinates.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/AbsCoordinatesIntr.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/AbsCoordinatesIntr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/RelCoordinates.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/RelCoordinatesIntr.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/config/RelCoordinatesIntr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/game/Game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfig.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfigLoader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/config/AppConfigLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/CommonDefines.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/App.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
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

if(CMAKE_BUILD_TYPE MATCHES Debug)
message("Debug build")
	target_compile_definitions(
		${PROJECT_NAME}
			PRIVATE
				-DDEBUG=1
	)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
message("Release build")
	target_compile_definitions(
		${PROJECT_NAME}
			PRIVATE
				-DNDEBUG=1
	)
endif()
