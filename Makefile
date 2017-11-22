CC=gcc
flags = -w -lSDL2
objects = main.o
targets = Cythen

all: $(targets)
	make $(targets)

Cythen: $(objects)
	$(CC) $(flags) -o $@ main.o

main.o:

.PHONY: clean
clean:
	rm $(targets) $(objects)
