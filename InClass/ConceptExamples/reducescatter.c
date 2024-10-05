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

  	int counts[size];
	int number[size];
	for(int i = 0; i<size; i++){
		number[i] = rank*size+i;
		counts[i] = 1;
	}
	int result;
	MPI_Reduce_scatter(number, &result, counts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printf("The sum of Column %d of the matrix: %d\n",rank, result);

	MPI_Finalize();
}
