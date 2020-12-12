#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "cudd.h"
#include "structs/tree.h"
#include "structs/list.h"

void print_dd (DdManager *gbm, DdNode	*dd, int n, int pr )
{
    printf("DdManager nodes: %ld | ", Cudd_ReadNodeCount(gbm)); /*Reports the number of live nodes in BDDs and ADDs*/
    printf("DdManager vars: %d | ", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existance*/
    printf("DdManager reorderings: %d | ", Cudd_ReadReorderings(gbm) ); /*Returns the number of times reordering has occurred*/
    printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm) ); /*Returns the memory in use by the manager measured in bytes*/
    Cudd_PrintDebug(gbm, dd, n, pr);	// Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
}

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
    DdNode *a, *b, *c;
    a = Cudd_bddNewVar(gbm);
    b = Cudd_bddNewVar(gbm);
    c = Cudd_bddNewVar(gbm);

    DdNode *bdd;
    bdd = Cudd_bddXor(gbm, a, b);

    c = Cudd_Not(c);
    bdd = Cudd_bddNand(gbm, bdd, c);
    
    // print_dd (gbm, bdd, 2,4);	/*Print the dd to standard output*/
    Cudd_Ref(bdd); /*Increases the reference count of a node*/
    bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
    sprintf(filename, "./bdd/graph.dot"); /*Write .dot filename to a string*/
    Cudd_Quit(gbm);
    // write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/

    // Opening 'formulas.txt'
    // Putting the lines in lists
    // And printing the lists before freeing them

    FILE *filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("formulas.txt", "r");

    while(fgets(buffer, bufferLength, filePointer)) {
        Tree tree = NULL;
        List head = readIntoList(buffer);
        printList(head);
        printf("\n");
        int i = createTree(&tree, &head);
        printf("%d\n", i);
        printTree(tree);
        printf("\n");
        freeList(head);
        freeTree(tree);
    }

    fclose(filePointer);
    return 0;
}
