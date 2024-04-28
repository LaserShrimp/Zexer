cmake_minimum_required(VERSION 3.0)
project(Zexer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
		${SOURCES}
		./src/Animation.cpp
		./src/AnimationHandler.cpp
		./src/Enemy.cpp
		./src/Game.cpp
		./src/gameAddOns.c
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
		./include/Animation.hpp
		./include/AnimationHandler.hpp
		./include/Enemy.hpp
		./include/Game.hpp
		./include/gameAddOns.h
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
		./include/defines.h)

add_executable(zexer ${SOURCES})
target_include_directories(zexer PRIVATE ./include/)
