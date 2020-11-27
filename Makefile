CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall

bdd.out: bdd.c structures/tree.c structures/list.c
	$(CC) $(CFLAGS) -I cudd-3.0.0/util -I cudd-3.0.0/cudd -I cudd-3.0.0 -I cudd-3.0.0/st -I cudd-3.0.0/mtr -I cudd-3.0.0/epd $^ cudd-3.0.0/cudd/.libs/libcudd.a -lm -o bdd.out

get-dependencies:
	wget https://www.davidkebo.com/source/cudd_versions/cudd-3.0.0.tar.gz
	tar xvf cudd-3.0.0.tar.gz
	cd cudd-3.0.0 && ./configure --enable-dddmp --enable-obj
	cd cudd-3.0.0 && make

show:
	./bdd.out
	dot -Tps bdd/graph.dot -o bdd/graph.ps
	evince bdd/graph.ps

clean:
	rm bdd.out