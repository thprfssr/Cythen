CC=gcc
flags = -w -lm -lSDL2 -lSDL2_image
objects = main.o game.o window.o tiles.o controls.o camera.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ $(objects)

main.o: game.h window.h tiles.h controls.h
game.o: window.h game.h tiles.h camera.h
window.o: window.h
tiles.o: game.h tiles.h
controls.o: controls.h

.PHONY: clean
clean:
	rm $(targets) $(objects)
