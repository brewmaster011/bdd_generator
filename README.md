# Summary of Repository

In the repository you will find the code in bdd.c and the folder bdd where you will find the graphs created by the program.

The program right now created trees and bdds of all the formulas in the `formulas.txt` file. The formulas can be in the format of normal propositional formulas with operators `&`, `|`, `~` and brackets `(` `)`. The program only allows for the atomic propositions 'a', 'b', 'c' and 'd'.

The resulting `.dot` files are in the folder "bdd". The program creates .dot files for all the formulas in the `formulas.txt` file. These can be visualized with the graphviz package.

## Compiling

In order to compile the bdd.c file you will first need to install CUDD version 3.0.0 in this directory. This can be done by running `make get-dependencies`

After downloading and installing you can run `make` in this folder and this will compile the executable bdd.out and create the folder 'bdd' if it does not exist.

You can then run the program with `./bdd.out`

## Opening the graphs

After running the bdd executable we will have binary decision diagrams of the formulas input into the program. 
In order to vizualize the graphs, with graphviz installed run:

```bash
make all-jpg-files
```

This will make a `.jpg` file for each of the `.dot` files in the bdd folder.


## Program Output

When running the program you will see some output from each of the formulas input in the program. First you will se the number of the formula and the formula itself. 

Below that we have a summary of the DdManager with the number of nodes and the number of variables of the manager itself. 

After those we see some data for the bdd itself. First we see the number of nodes, leaves and minterms of the bdd. Then we have a list of all the nodes and their properties (ID, index, etc). Lastly we the disjoint sum of the profucts for the bdd.