CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = main.o tile.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ main.o

main.o: game.h
tile.o:

.PHONY: clean
clean:
	rm $(targets) $(objects)
