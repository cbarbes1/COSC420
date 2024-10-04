#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
	//srand(time(NULL));
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand(time(NULL) + rank);
  	if(rank == 0) {
		int number;
		int num_to_send = rand()%100+1;
		printf("Rank: %d has %d\n", rank, num_to_send);	
		MPI_Reduce(&num_to_send, &number, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
		printf("The max of the list of numbers is : %d\n", number);
	} else {
		int number;
		int num_to_send_child = rand()%100+1;
		printf("Rank: %d has %d\n", rank, num_to_send_child);
		MPI_Reduce(&num_to_send_child, &number, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  	}

	MPI_Finalize();
}
