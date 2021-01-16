SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CC=gcc
CFLAGS=-O2 -Wall

main:
	${CC} -o falling_sand.out ./main.c ${CFLAGS} ${SDL_LDFLAGS} ${SDL_CFLAGS}
