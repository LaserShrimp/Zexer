all: game
CPP= g++ --std=c++11 -Wall
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
#g++ -Wall -o game main.cpp Ship.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	
Ship.o: Ship.cpp Ship.hpp
	$(CPP) -c Ship.cpp $(LIBS)
	
Enemy.o: Enemy.cpp Enemy.hpp
	$(CPP) -c Enemy.cpp $(LIBS)
	
Player.o: Player.cpp Player.hpp
	$(CPP) -c Player.cpp $(LIBS)
	
Missile.o: Missile.cpp Missile.hpp
	$(CPP) -c Missile.cpp $(LIBS)
	
main.o: main.cpp
	$(CPP) -c main.cpp $(LIBS)
	
game: main.o Ship.o Enemy.o Player.o Missile.o
	$(CPP) -o zexer.exe Ship.o Enemy.o Player.o Missile.o main.o $(LIBS)
	
clean:
	rm -rf *.o