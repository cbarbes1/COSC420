/* Author: Cole Barbes Spencer Presley
* Data created: 11/05/24
* Purpose: create a binary tree in parallel
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "functions.c"

int main(int argc, char **argv){
    if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	srand(time(NULL));

	int num_nodes = atoi(argv[1])/8;

    double start = omp_get_wtime();
    struct node *head = NULL;

    int BT_num_nodes = 0;


    // parallel creation of 8 binary trees to count number of nodes under 0.5
    // the reduction, schedule, and private are all needed to manage the threads access and make sure every thread has a task
    #pragma omp parallel for reduction(+:BT_num_nodes) num_threads(8) schedule(static, 8) private(num_nodes)
    for(int i = 0; i<8; i++)
    {
        struct node *localhead = NULL;
        localhead = CreateTree(localhead, num_nodes, 0);
        BT_num_nodes += BTTraverseCountl(localhead);
    }

    printf("Here is the size of the tree  with value less than 0.5 %d \n", BT_num_nodes);

    start = (double)omp_get_wtime() - start;

    printf("Parallel program took %fs\n", start);


    delete(head);
    return 0;
}
