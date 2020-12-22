CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall

bdd.out: bdd.c structs/tree.c structs/list.c | directory
	$(CC) $(CFLAGS) -I cudd-3.0.0/util -I cudd-3.0.0/cudd -I cudd-3.0.0 -I cudd-3.0.0/st -I cudd-3.0.0/mtr -I cudd-3.0.0/epd $^ cudd-3.0.0/cudd/.libs/libcudd.a -lm -o bdd.out

get-dependencies:
	wget https://www.davidkebo.com/source/cudd_versions/cudd-3.0.0.tar.gz
	tar xvf cudd-3.0.0.tar.gz
	cd cudd-3.0.0 && ./configure --enable-dddmp --enable-obj
	cd cudd-3.0.0 && make

bdd/graph_%.jpg: bdd/graph_%.dot
	dot -Tjpg $< -o $@

all-jpg-files: $(addsuffix .jpg, $(addprefix bdd/graph_, $(shell seq 1 31)))

directory:
	mkdir -p bdd

clean:
	rm bdd.out info.txt

.PHONY: clean all-jpg-files