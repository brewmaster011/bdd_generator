/*
* FILENAME: tutorial.c
* Overview: BDD tutorial
* AUTHOR: David Kebo Houngninou
*/

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "cudd.h"
#include "tree.h"

/**
 * Print a dd summmary
 * pr = 0 : prints nothing
 * pr = 1 : prints counts of nodes and minterms
 * pr = 2 : prints counts + disjoint sum of product
 * pr = 3 : prints counts + list of nodes
 * pr > 3 : prints counts + disjoint sum of product + list of nodes
 * @param the dd node
 */
void print_dd (DdManager *gbm, DdNode	*dd, int n, int pr )
{
    printf("DdManager nodes: %ld | ", Cudd_ReadNodeCount(gbm)); /*Reports the number of live nodes in BDDs and ADDs*/
    printf("DdManager vars: %d | ", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existance*/
    printf("DdManager reorderings: %d | ", Cudd_ReadReorderings(gbm) ); /*Returns the number of times reordering has occurred*/
    printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm) ); /*Returns the memory in use by the manager measured in bytes*/
    Cudd_PrintDebug(gbm, dd, n, pr);	// Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
}


/**
 * Writes a dot file representing the argument DDs
 * @param the node object
 */
void write_dd (DdManager *gbm, DdNode	*dd, char* filename)
{
    FILE *outfile; // output file pointer for .dot file
    outfile = fopen(filename,"w");
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, NULL, NULL, outfile);	// dump the function to .dot file
    free(ddnodearray);
    fclose (outfile); // close the file */
}

// This program creates a single BDD variable
int main (int argc, char *argv[])
{
    DdManager *gbm;	/* Global BDD manager. */
    char filename[30]; 
    gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
    DdNode *xa = Cudd_bddNewVar(gbm); /*Creat new BDD variables*/
    DdNode *xb = Cudd_bddNewVar(gbm);
    DdNode *xc = Cudd_bddNewVar(gbm);

    DdNode *firstAnd = Cudd_bddAnd(gbm, Cudd_Not(xa), Cudd_Not(xb));
    firstAnd = Cudd_bddAnd(gbm, firstAnd, Cudd_Not(xc));

    DdNode *secondAnd = Cudd_bddAnd(gbm, Cudd_Not(xa), xb);
    secondAnd = Cudd_bddAnd(gbm, secondAnd, xc);

    DdNode *thirdAnd = Cudd_bddAnd(gbm, Cudd_Not(xa), Cudd_Not(xb));
    thirdAnd = Cudd_bddAnd(gbm, thirdAnd, xc);

    DdNode *fourthAnd = Cudd_bddAnd(gbm, xa, xb);
    fourthAnd = Cudd_bddAnd(gbm, fourthAnd, Cudd_Not(xc));

    DdNode *bdd = Cudd_bddOr(gbm, firstAnd, secondAnd);
    bdd = Cudd_bddOr(gbm, bdd, thirdAnd);
    bdd = Cudd_bddOr(gbm, bdd, fourthAnd);
    
    Cudd_Ref(bdd); /*Increases the reference count of a node*/
    bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
    print_dd (gbm, bdd, 2,4);	/*Print the dd to standard output*/
    sprintf(filename, "./bdd/graph.dot"); /*Write .dot filename to a string*/
    write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
    Cudd_Quit(gbm);

    tree t = newTreeNode('a');
    t->left = newTreeNode('b');
    t->right = newTreeNode('c');

    freeTree(t);

    return 0;
}
