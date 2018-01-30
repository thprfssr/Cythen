CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = game.o tile.o window.o csv_parser.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ game.o window.o tile.o csv_parser.o

game.o: window.h game.h
window.o: window.h
tile.o: tiles.h
csv_parser.o: csv_parser.h

.PHONY: clean
clean:
	rm $(targets) $(objects)
