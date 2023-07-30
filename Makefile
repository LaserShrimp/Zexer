all: game
CPP= g++ --std=c++11 -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
#`sdl2-config --cflags --libs`
#-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	
Ship.o: Ship.cpp Ship.hpp
	$(CPP) -c Ship.cpp $(LIBS)
	
Enemy.o: Enemy.cpp Enemy.hpp
	$(CPP) -c Enemy.cpp $(LIBS)
	
Player.o: Player.cpp Player.hpp
	$(CPP) -c Player.cpp $(LIBS)
	
Missile.o: Missile.cpp Missile.hpp
	$(CPP) -c Missile.cpp $(LIBS)
	
InputState.o: InputState.cpp InputState.hpp
	$(CPP) -c InputState.cpp $(LIBS)
	
GameInterface.o: GameInterface.cpp GameInterface.hpp
	$(CPP) -c GameInterface.cpp  $(LIBS)
	
Animation: Animation.cpp Animation.hpp
	$(CPP) -c Animation.cpp  $(LIBS)
	
Unit1.o: Unit1.cpp Unit1.hpp
	$(CPP) -c Unit1.cpp  $(LIBS)
	
main.o: main.cpp defines.h
	$(CPP) -c main.cpp $(LIBS)
	
game: main.o Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o
	$(CPP) -o zexer Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o main.o $(LIBS)
	
clean:
	rm -rf *.o
