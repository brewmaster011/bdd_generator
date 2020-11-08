# Summary of Repository

In the repository you will find the code that compiles into the executable bdd.out, the executable itself and the folder bdd where you will find the graphs created by the executable.

I would have liked to upload the library here aswell in order to compile immeadetly after cloning the repository but this was not possible as some files were too large for github.

# Compiling

In order to compile the code, move the cudd-3.0.0 library into the main folder. Afterwards run the following command (where the name of the file to be compiled is bdd.c):

```

gcc -I cudd-3.0.0/util -I cudd-3.0.0/cudd -I cudd-3.0.0 -I cudd-3.0.0/st -I cudd-3.0.0/mtr -I cudd-3.0.0/epd bdd.c cudd-3.0.0/cudd/.libs/libcudd.a -lm -o bdd.out
```

This will create an executable called bdd in the main folder which can be run by simply typing ./bdd

# Opening the File

After running the bdd executable we will gave a graph.dot file inside the bdd folder.
In order to vizualize the graph, with graphviz installed run:

```

dot -Tps bdd/graph.dot bdd/graph.ps
```

This will return in the same folder the graph in ps format (in order to maintain the quality of the graph). We can change the type of file outputed as desired.