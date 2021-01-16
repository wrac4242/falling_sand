.PHONY: all clean

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDLIBS := $(shell sdl2-config --libs)

CFLAGS = $(SDL_CFLAGS)
LDLIBS = -O2 -Wall $(SDL_LDLIBS)

GAME = falling_sand

all: $(GAME)

$(GAME): falling_sand.o

clean:
	$(RM) *.o $(GAME)
