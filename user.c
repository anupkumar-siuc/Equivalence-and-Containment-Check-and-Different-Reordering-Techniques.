#include"given.h"
#include <time.h>
void test( NODE *graph, int Max,DdManager *manager )

{

DdNode *temp1,*temp2,*temp3,*temp4,*fun0,*fun1,*fun2,*fun3,*efun1,*efun2;        //function bdds
int i,j=0,k,nns,old=0,E1,E2,nns1,nns2,nns3,nns4=0,w;

LIST *temp;
printf("\nBDD_Demo_Start\n*************\n");	
manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); //intializing CUDD package manger
//Cudd_AutodynEnable(manager, CUDD_REORDER_WINDOW2);
//Cudd_ReduceHeap(manager, 0,3000);


//Cudd_ReorderingType rd_type[6]={ CUDD_REORDER_RANDOM, CUDD_REORDER_SIFT, CUDD_REORDER_GROUP_SIFT, CUDD_REORDER_SYMM_SIFT,CUDD_REORDER_GROUP_SIFT_CONV,CUDD_REORDER_WINDOW2,CUDD_REORDER_ANNEALING };

//this loop is for easy reordering

/*1st for loop starts*/
for ( i=1; i<= Max ; i++)

  {

	if ( graph[i].typ != 0 )
	{

	switch(graph[i].typ) 
		{
	case INPT:
		graph[i].fun=Cudd_bddIthVar(manager, j);  Cudd_Ref(graph[i].fun);
		//printf("........BDD of INPT=%d........ \n",i); 
		//Cudd_PrintMinterm(manager,graph[i].fun);
		j++;
		break;

	case NAND:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddAnd(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  //tmp2= a
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  //tmp1=a 
		//printf("level_NAND_wokrs \n");
		//printf("for gate=%d  fan.in_list=%d\n",i,temp->id);		
		temp=temp-> nxt;	
		}

		graph[i].fun=Cudd_Not(temp1);	Cudd_Ref(graph[i].fun);	Cudd_RecursiveDeref(manager,temp1);
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0	
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {
		//printf("NAND_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break;

	case FROM:	
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=graph[temp->id].fun; Cudd_Ref(graph[i].fun);
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0	
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("FROM_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break;

	case AND: 
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddAnd(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  //tmp2= a
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  //tmp1=a 
		//printf("level_AND_wokrs \n");
		//printf("for gate=%d  fan.in_list=%d\n",i,temp->id);		
		temp=temp-> nxt;	
		}
		graph[i].fun=temp1; Cudd_Ref(graph[i].fun); Cudd_RecursiveDeref(manager,temp1);  
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0	
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("AND_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break; 

	case OR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddOr(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  //tmp2= a
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  //tmp1=a 
		//printf("level_OR_wokrs \n");
		//printf("for gate=%d  fan.in_list=%d\n",i,temp->id);		
		temp=temp-> nxt;	
		}		
		graph[i].fun=temp1; Cudd_Ref(graph[i].fun); Cudd_RecursiveDeref(manager,temp1);  
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0	
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("OR_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break; 

	case NOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddOr(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  //tmp2= a
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  //tmp1=a 
		//printf("level_NOR_wokrs \n");
		//printf("for gate=%d  fan.in_list=%d\n",i,temp->id);		
		temp=temp-> nxt;	
		}
		graph[i].fun=Cudd_Not(temp1);	Cudd_Ref(graph[i].fun);	Cudd_RecursiveDeref(manager,temp1);
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0		
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("NOR_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break; 

	case XOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager); Cudd_Ref(temp1);
		while (temp!= NULL) {
		temp2=Cudd_bddAnd(manager, temp1, Cudd_Not(graph[temp->id].fun) ); Cudd_Ref(temp2); 
		temp3=Cudd_bddAnd(manager, Cudd_Not(temp1),  graph[temp->id].fun ); Cudd_Ref(temp3); Cudd_RecursiveDeref (manager, temp1);
		temp1=Cudd_bddOr(manager, temp2, temp3); Cudd_Ref(temp1); Cudd_RecursiveDeref (manager, temp2); Cudd_RecursiveDeref (manager, temp3);
		temp=temp->nxt;
		}
		graph[i].fun=temp1; Cudd_Ref( graph[i].fun );	Cudd_RecursiveDeref (manager, temp1);	
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0		
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("XOR_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break; 
	
	case XNOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager); Cudd_Ref(temp1);
		while (temp!= NULL) {
		temp2=Cudd_bddAnd(manager, temp1, Cudd_Not(graph[temp->id].fun) ); Cudd_Ref(temp2); 
		temp3=Cudd_bddAnd(manager, Cudd_Not(temp1),  graph[temp->id].fun ); Cudd_Ref(temp3); Cudd_RecursiveDeref (manager, temp1);
		temp1=Cudd_bddOr(manager, temp2, temp3); Cudd_Ref(temp1); Cudd_RecursiveDeref (manager, temp3); Cudd_RecursiveDeref (manager, temp2);
		temp=temp->nxt;
		}
		graph[i].fun=Cudd_Not(temp1); Cudd_Ref( graph[i].fun );	Cudd_RecursiveDeref (manager, temp1);	
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0		
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("XNOR_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break;  

	case BUFF:
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=graph[temp->id].fun; Cudd_Ref(graph[i].fun);
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0		
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("BUFFER_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break; 

	case NOT:
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=Cudd_Not( graph[temp->id].fun );	Cudd_Ref(graph[i].fun);	
		/*Maximum_number_of_node_in_the_manager_STARTS*/		
		nns=Cudd_DagSize(graph[i].fun); //nns= new node size , old= old node size i.e., 0		
		if (nns>old) old=nns;
		/*Maximum_number_of_node_in_the_manager_ENDS*/
		if(graph[i].po==1) {			
		//printf("AND_BDD_function_for=%d\n", i);
		//Cudd_PrintMinterm(manager,graph[i].fun);
			}
		break;  
		
		} /*end of switch*/

	} /*end of if*/

 } /*end of 1st for loop*/
nns1=old;
//printf("max_num_node %d\n",max_num_node);

printf("\nMaximum_number_of_node_in_the_manager_for_the_Generated_Circuit=%d\n",old);

/*Equivalence_and_Containment_check_status_starts*/
for (i=0; i<Max; i++) 
{
  if (graph[i].po != 0)
	{
	for(k=i+1; k<=Max; k++)
		{
		if( (k != i) && (graph[k].po != 0) )
			{
			printf("\nEquivalence_and_Containment_check_status_for_NODE %d and %d :\n", i, k);
			printf("*****************************************************************\n");
			temp3=Cudd_bddAnd(manager,graph[k].fun,Cudd_Not(graph[i].fun) );  Cudd_Ref(temp3); 
			efun1=temp3;  Cudd_Ref(efun1);  Cudd_RecursiveDeref(manager,temp3);  //doing efun1=F1'.F2
			
			temp3=Cudd_bddAnd(manager, graph[i].fun,Cudd_Not(graph[k].fun) );  Cudd_Ref(temp3);  
			efun2=temp3;  Cudd_Ref(efun2);  Cudd_RecursiveDeref(manager,temp3);  //doing efun1=F1.F2'
			
			E1=Cudd_IsConstant(efun1) && Cudd_IsComplement(efun1);	Cudd_RecursiveDeref(manager, efun1);	//F1'.F2=0 if E1=1
			E2=Cudd_IsConstant(efun2) && Cudd_IsComplement(efun2);	Cudd_RecursiveDeref(manager, efun2);	//F1.F2'=0 if E2=1
			
			if(E1==1 && E2==1) { printf("Function F1, F2 is Equivalent and not contained in each other\n");}
			else if (E2==1 && E1!=1){printf("F1 is contained in F2 but is not Equivalent\n");}
			else if (E1==1 && E2!=1){printf("F2 is contained in F1 but is not Equivalent\n");}	
			else printf("Function F1 and F2 is not Equivalent also not contained in each other\n");
			}
		}
	}
}

/*****************************************************************************************************************************************************/
/*2nd for loop starts*/
enum  Cudd_ReorderingType { CUDD_REORDER_RANDOM, CUDD_REORDER_SIFT, CUDD_REORDER_GROUP_SIFT, CUDD_REORDER_SYMM_SIFT,CUDD_REORDER_GROUP_SIFT_CONV,CUDD_REORDER_WINDOW2,CUDD_REORDER_ANNEALING };
clock_t tic, toc; //clock 
for(w=0; w<=6; w++)   
{

if (w==0)printf("CUDD_REORDER_RANDOM applied\n");
if (w==1)printf("CUDD_REORDER_SIFT applied\n");
if (w==2)printf("CUDD_REORDER_GROUP_SIFT applied\n");
if (w==3)printf("CUDD_REORDER_SYMM_SIFT applied\n");
if (w==4)printf("CUDD_REORDER_GROUP_SIFT_CONV applied\n");
if (w==5)printf("CUDD_REORDER_WINDOW2 applied\n");
if (w==6)printf("CUDD_REORDER_ANNEALING applied\n");

for(i=0;i<=Max;i++)  {
	if ( graph[i].typ != 0 )
	{
	switch(graph[i].typ) 
		{
	case NAND:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break;
   
    case AND:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break;   

    case OR:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 

    case NOR:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 
   
    case BUFF:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 

    case FROM:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 

    case XOR:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 

    case XNOR:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 

    case NOT:
		nns2=Cudd_DagSize(graph[i].fun);
		if (nns2> nns1/2) {
        tic = clock();
        Cudd_ReduceHeap(manager,w,0);
       	nns3=Cudd_DagSize(graph[i].fun);
        printf("For node %d number of max node in manager before reordering %d after reordering %d\n",i,nns2,nns3);
          if(nns4<nns3) nns4=nns3;
        }
		break; 
			
}  }  } 
  //cpu time 
  toc = clock();
  printf("Max node in manager after reordering is: %d\n",nns4 );
  nns4=0;
  printf("Total time taken by CPU: %f\n\n", (double)(toc - tic) / CLOCKS_PER_SEC );
 }

Cudd_Quit(manager);   //closing the cudd package manager
printf("\n\nBDD Demo End\n");  
return;	

}
