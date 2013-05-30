CC = gcc -g

DATA_1 = ../bin/busca

FILES_1 = main_avl.o \
		avl-tree.o 

all: $(DATA_1)

$(DATA_1): $(FILES_1)
	$(CC) -o $@ $+

clean:
	rm -f *.bak core* *.~*

hurdle:
	rm -f *.o $(DATA_1)
