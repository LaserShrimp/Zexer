all: Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o Vect.o gameAddOns.o Game.o Particle.o Wave.o AnimationHandler.o Item.o main.o game
CPP= g++ --std=c++20 -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -I./include/
SRC = ./src/
# `sdl2-config --cflags --libs`
# -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	
Ship.o: $(SRC)Ship.cpp 
	$(CPP) -c $(SRC)Ship.cpp $(LIBS) $(CFLAGS)
	
Enemy.o: $(SRC)Enemy.cpp
	$(CPP) -c $(SRC)Enemy.cpp $(LIBS) $(CFLAGS)
	
Player.o: $(SRC)Player.cpp
	$(CPP) -c $(SRC)Player.cpp $(LIBS) $(CFLAGS)
	
Missile.o: $(SRC)Missile.cpp
	$(CPP) -c $(SRC)Missile.cpp $(LIBS) $(CFLAGS)
	
InputState.o: $(SRC)InputState.cpp
	$(CPP) -c $(SRC)InputState.cpp $(LIBS) $(CFLAGS)
	
GameInterface.o: $(SRC)GameInterface.cpp
	$(CPP) -c $(SRC)GameInterface.cpp  $(LIBS) $(CFLAGS)
	
Animation.o: $(SRC)Animation.cpp
	$(CPP) -c $(SRC)Animation.cpp  $(LIBS) $(CFLAGS)
	
Unit1.o: $(SRC)Unit1.cpp
	$(CPP) -c $(SRC)Unit1.cpp  $(LIBS) $(CFLAGS)
	
Vect.o: $(SRC)Vect.cpp
	$(CPP) -c $(SRC)Vect.cpp  $(LIBS) $(CFLAGS)
	
gameAddOns.o: $(SRC)gameAddOns.c
	$(CPP) -c $(SRC)gameAddOns.c  $(LIBS) $(CFLAGS)

Game.o: $(SRC)Game.cpp
	$(CPP) -c $(SRC)Game.cpp  $(LIBS) $(CFLAGS)

Particle.o: $(SRC)Particle.cpp
	$(CPP) -c $(SRC)Particle.cpp  $(LIBS) $(CFLAGS)

Wave.o: $(SRC)Wave.cpp
	$(CPP) -c $(SRC)Wave.cpp  $(LIBS) $(CFLAGS)
	
AnimationHandler.o: $(SRC)AnimationHandler.cpp
	$(CPP) -c $(SRC)AnimationHandler.cpp  $(LIBS) $(CFLAGS)
	
Item.o: $(SRC)Item.cpp
	$(CPP) -c $(SRC)Item.cpp  $(LIBS) $(CFLAGS)
	
main.o: $(SRC)main.cpp
	$(CPP) -c $(SRC)main.cpp $(LIBS) $(CFLAGS)
	
# compile: 
# 	$(CPP) -c $(SRC)*.c $(SRC)*.cpp $(CFLAGS) $(LIBS)

game: Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o Vect.o gameAddOns.o Game.o Particle.o Wave.o AnimationHandler.o Item.o main.o
	$(CPP) -o zexer *.o $(LIBS)
clean:
	rm -rf *.o
