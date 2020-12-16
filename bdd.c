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

DdNode * create_bdd(DdManager *gbm, Tree *t, DdNode *a, DdNode *b, DdNode *c){

    if(!*t) return NULL;

    if((*t)->left == NULL && (*t)->right == NULL){
        switch ((*t)->data){
        case 'a':
            if(a == NULL) a = Cudd_bddNewVar(gbm);
            return a;
            break;
        
        case 'b':
            if(b == NULL) b = Cudd_bddNewVar(gbm);
            return b;
            break;

        case 'c':
            if(c == NULL) c = Cudd_bddNewVar(gbm);
            return c;
            break;
        
        default:
            break;
        }
    }

    DdNode *left = create_bdd(gbm, &((*t)->left), a, b, c);
    DdNode *right = create_bdd(gbm, &((*t)->right), a, b, c);

    switch((*t)->data){
    case '&':
        return Cudd_bddAnd(gbm, left, right);
        break;
    
    case '|':
        return Cudd_bddOr(gbm, left, right);
        break;

    case '~':
        return Cudd_Not(left);
        break;
    
    default:
        break;
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    char filename[30]; 

    // Opening 'formulas.txt'
    // Putting the lines in lists
    // And printing the lists before freeing them

    Tree tree = NULL;
    List head;
    int i = 0;
    int name = 1;

    FILE *fptr;
    int bufferLength = 225;
    char buffer[bufferLength];

    fptr = fopen("formulas.txt", "r");

    while(fgets(buffer, bufferLength, fptr)) {
        DdManager *gbm;	/* Global BDD manager. */
        DdNode *a, *b, *c;
        a = b = c = NULL;
        
        gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
        head = readIntoList(buffer);
        printList(head);
        printf("\n");
        i = createTree(&tree, &head);

        if(i){
            DdNode *bdd = create_bdd(gbm, &tree, a, b, c);
            Cudd_Ref(bdd);
            bdd = Cudd_BddToAdd(gbm, bdd);
            sprintf(filename, "./bdd/graph_%d.dot", name);
            print_dd (gbm, bdd, 2,4);	/*Print the dd to standard output*/
            write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/

            printTree(tree);
            printf("\n");
            printf("\n");
            name++;

        } else {
            printf("Tree failed.\n");
            return 1;
        }
        Cudd_Quit(gbm);
    }

    freeList(head);
    freeTree(tree);

    fclose(fptr);
    i++;
    return 0;
}
