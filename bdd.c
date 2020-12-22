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
    printf("DdManager vars: %d", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existance*/
    printf("\n");
    Cudd_PrintDebug(gbm, dd, n, pr);	// Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
    // Prints more detailed information about dd into info.tx
    FILE *pointer ;
    pointer = fopen("info.txt", "a+");
    Cudd_PrintInfo(gbm, pointer);
    fprintf(pointer, "\n");
    fclose(pointer);
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

DdNode * create_bdd(DdManager *gbm, Tree *t){

    if(!*t) return NULL;

    if((*t)->left == NULL && (*t)->right == NULL){
        switch ((*t)->data){
        case 'a':
            return Cudd_bddIthVar(gbm, 0);
            break;
        
        case 'b':
            return Cudd_bddIthVar(gbm, 1);
            break;

        case 'c':
            return Cudd_bddIthVar(gbm, 2);
            break;

        case 'd':
            return Cudd_bddIthVar(gbm, 3);
        
        default:
            break;
        }
    }

    DdNode *left = create_bdd(gbm, &((*t)->left));
    DdNode *right = create_bdd(gbm, &((*t)->right));

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
        
        gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
        head = readIntoList(buffer);

        printf("Formula %d: ", name);
        printList(head);
        printf("\n");

        i = createTree(&tree, &head);

        if(i){
            DdNode *bdd = create_bdd(gbm, &tree);
            Cudd_Ref(bdd);
            bdd = Cudd_BddToAdd(gbm, bdd);
            sprintf(filename, "./bdd/graph_%d.dot", name);
            print_dd (gbm, bdd, 4, 4);	/*Print the dd to standard output*/
            write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
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
    return 0;
}
