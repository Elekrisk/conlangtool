SOURCE = $(wildcard src/*.c)
HEADER = $(wildcard src/*.h)

conlangtool : $(SOURCE) $(HEADER)
	gcc $(SOURCE) -lncurses -o conlangtool

