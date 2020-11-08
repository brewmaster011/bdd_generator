# Compiling

In order to compile the code, cd into the cudd-3.0.0 folder and run:

```

gcc -I util -I cudd -I cudd-3.0.0 -I st -I mtr -I epd test.c cudd/.libs/libcudd.a -lm -o ../bdd
```

This will create an executable called bdd in the main folder which can be run by simply typing ./bdd

# Opening the file

After running the bdd executable we will gave a graph.dot file inside the bdd folder.
In order to vizualize the graph, with graphviz installed run:

```

dot -Tps bdd/graph.dot bdd/graph.ps
```

This will return in the same folder the graph in ps format (in order to maintain the quality of the graph). We can change the type of file outputed as desired.