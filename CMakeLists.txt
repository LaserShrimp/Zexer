cmake_minimum_required(VERSION 3.0)
project(Zexer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
		${SOURCES}
		./src/gameAddOns.cpp
		./src/Animation.cpp
		./src/AnimationHandler.cpp
		./src/Enemy.cpp
		./src/Game.cpp
		./src/GameInterface.cpp
		./src/InputState.cpp
		./src/Item.cpp
		./src/main.cpp
		./src/Missile.cpp
		./src/Particle.cpp
		./src/Player.cpp
		./src/Ship.cpp
		./src/Unit1.cpp
		./src/Vect.cpp
		./src/Wave.cpp
		./src/SDLMenu.cpp
		./include/gameAddOns.hpp
		./include/Animation.hpp
		./include/AnimationHandler.hpp
		./include/Enemy.hpp
		./include/Game.hpp
		./include/GameInterface.hpp
		./include/InputState.hpp
		./include/Item.hpp
		./include/Missile.hpp
		./include/Particle.hpp
		./include/Player.hpp
		./include/Ship.hpp
		./include/Unit1.hpp
		./include/Vect.hpp
		./include/Wave.hpp
		./include/SDLMenu.hpp
		./include/defines.h)

add_executable(zexer ${SOURCES})
target_link_libraries(zexer SDL2 SDL2_image SDL2_mixer SDL2_ttf)
target_include_directories(zexer PRIVATE ./include/)