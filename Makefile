CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = game.o window.o parser.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ game.o window.o parser.o

game.o: window.h game.h
window.o: window.h
parser.o: parser.h

.PHONY: clean
clean:
	rm $(targets) $(objects)
