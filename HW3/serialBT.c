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

	int num_nodes = atoi(argv[1]);

    double start = omp_get_wtime();
    struct node *head = CreateNode();
    
    
    for(int i = 0; i<num_nodes; i++){
        struct node *newNode = CreateNode();
        insert(&head, &newNode);
    }


    int BT_num_nodes = BTTraverseCountl(head);

    printf("Here is the size of the tree  with value less than 0.5 %d \n", BT_num_nodes);

    // BT_num_nodes = BTTraverseCount(head);

    // printf("Here is the size of the tree %d \n", BT_num_nodes);

    start = (double)omp_get_wtime() - start;

    printf("Serial program took %fs\n", start);


    delete(head);
}
