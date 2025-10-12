OBJS=Ship.o Enemy.o Player.o Missile.o InputState.o GameInterface.o Animation.o Unit1.o Vect.o gameAddOns.o Game.o Particle.o Wave.o AnimationHandler.o Item.o main.o
CPP=g++ --std=c++2a -Wall
ifeq ($(OS), Windows_NT)
	LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
else
	LIBS=$(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer)
endif
CFLAGS=-I./include/
SRC =./src/
# `sdl2-config --cflags --libs`
# -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all: zexer

zexer: $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: $(SRC)%.c
	$(CPP) $(CFLAGS) -c $<

%.o:$(SRC)%.cpp
	$(CPP) $(CFLAGS) -c $<

clean:
	rm -rf *.o
