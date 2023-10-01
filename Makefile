all: compile game
CPP= g++ --std=c++11 -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -I./include/
SRC = ./src/
# `sdl2-config --cflags --libs`
# -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	
# Ship.o: Ship.cpp Ship.hpp
# 	$(CPP) -c Ship.cpp $(LIBS)
# 	
# Enemy.o: Enemy.cpp Enemy.hpp
# 	$(CPP) -c Enemy.cpp $(LIBS)
# 	
# Player.o: Player.cpp Player.hpp
# 	$(CPP) -c Player.cpp $(LIBS)
# 	
# Missile.o: Missile.cpp Missile.hpp
# 	$(CPP) -c Missile.cpp $(LIBS)
# 	
# InputState.o: InputState.cpp InputState.hpp
# 	$(CPP) -c InputState.cpp $(LIBS)
# 	
# GameInterface.o: GameInterface.cpp GameInterface.hpp
# 	$(CPP) -c GameInterface.cpp  $(LIBS)
# 	
# Animation.o: Animation.cpp Animation.hpp
# 	$(CPP) -c Animation.cpp  $(LIBS)
# 	
# Unit1.o: Unit1.cpp Unit1.hpp
# 	$(CPP) -c Unit1.cpp  $(LIBS)
# 	
# Vect.o: Vect.cpp Vect.hpp
# 	$(CPP) -c Vect.cpp  $(LIBS)
# 	
# gameAddOns.o: gameAddOns.c gameAddOns.h
# 	$(CPP) -c gameAddOns.c  $(LIBS)
# 	
# main.o: main.cpp defines.h
# 	$(CPP) -c main.cpp $(LIBS)
	
# %.o: %.cpp
# 	$(CPP) -o $@ -c $(LIBS)
	
# game: main.o Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o Vect.o gameAddOns.o
# 	$(CPP) -o zexer Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o Vect.o gameAddOns.o main.o $(LIBS)
# 	
compile: 
	$(CPP) -c $(SRC)*.c $(SRC)*.cpp $(CFLAGS) $(LIBS)
game:
	$(CPP) -o zexer *.o $(LIBS)
clean:
	rm -rf *.o
