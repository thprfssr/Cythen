CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = game.o window.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ game.o window.o

game.o: window.h game.h
window.o: window.h

.PHONY: clean
clean:
	rm $(targets) $(objects)
