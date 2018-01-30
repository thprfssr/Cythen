CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = main.o tile.o window.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ main.o window.o

main.o: window.h game.h
window.o: window.h
tile.o:

.PHONY: clean
clean:
	rm $(targets) $(objects)
