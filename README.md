# Summary of Repository

In the repository you will find the code in bdd.c and the folder bdd where you will find the graphs created by the program.

The program right now created trees and bdds of all the formulas in the `formulas.txt` file. The formulas can be in the format of normal propositional formulas with operators `&`, `|`, `~` and brackets `(` `)`.

In the folder bdd there is the graph of the last formula in the file.

## Compiling

In order to compile the bdd.c file you will first need to install CUDD version 3.0.0 in this directory. This can be done by running `make get-dependencies`

After downloading and installing you can run `make` in this folder and this will compile the executable bdd.out. **Make sure there is a directory called `bdd` in this folder or the program will not work**.

You can then run the program with `./bdd.out`

## Opening the graph

After running the bdd executable we will gave a graph.dot file inside the bdd folder.
In order to vizualize the graph, with graphviz installed run:

```bash
dot -Tps bdd/graph.dot -o bdd/graph.ps
```

This will return in the same folder the graph in ps format (in order to maintain the quality of the graph). We can change the type of file outputed as desired. For example to convert to a jpeg:

```bash
dot -Tjpg bdd/graph.dot -o bdd/graph.jpg
```
