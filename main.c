#include "given.h"
/***************************************************************************************************************************
Main Function( write all new functions in user.c only and call them in main.c) 
Compile   Command: make
Execution Command: ./pro1 "input file" "output file"
****************************************************************************************************************************/
int main(int argc, char **argv)
{
FILE *fisc,*fout;                     //file pointers used for .isc file and output file
int Max,Bound;                        //maxnode id,Max nodes in a bdd of cct 
NODE *graph;                          //structure used to store the cct information in .isc file 
int a,b,c,d;                          //random variables


//Read the .isc file and store the information in graph structure
fisc=fopen(argv[1],"r");                           //file pointer to open .isc file 
graph=(NODE *) malloc(Mnod * sizeof(NODE));        //dynamic memory allocation for graph structure
Max=0; Max=ReadIsc(fisc,graph);                    //read .isc file and return index of last node in graph formed
fclose(fisc);                                      //close file pointer for .isc file
PrintCircuit(graph,Max);                           //print all members of graph structure

test (graph, Max, manager); //BDD user.c function declaration 

//maximum number of node
//printf("Max_Number_of_node_id= %d \n",Max);


manager=Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);  //intializing CUDD package manger
fout=fopen(argv[2],"w");                                      //file pointer to open .out file 

//void testbdd(manager, graph, Max); // forming of BDD declaration

//project 1:
//Form the bdd functions with PIs as default ordering and find the maximum node size
//Check the Equivalency and containment b/w each POs pair(f1,f2) of the cct and print in file
//Dereference the bdds
//form bdds using 7 reorder techiques and report the maximum node size and cpu time

printf("\nNo of Unreferenced Bdds %d\n", Cudd_CheckZeroRef(manager));
Cudd_Quit(manager);                                           //closing the cudd package manager
ClearCircuit(graph,Mnod);                                     //clear memeory for all members of graph
fclose(fout);                                                 //close the output file

return;
}//end of main
/****************************************************************************************************************************/
