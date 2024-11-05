#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

int main(int argc, char **argv)
{
	srand(time(NULL));
	MPI_Init(&argc, &argv);
	
	int size, rank;
	MPI_Request request;
	MPI_Status status;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char message[12] = "Hello World";

	if(rank == 0){
		for(int i = 1; i<size; i++){
			MPI_Isend(message, 12, MPI_CHAR, i, (i*10), MPI_COMM_WORLD, &request);
		}

		int flag = 0;
		MPI_Test(&request, &flag, &status);
		if(flag){
			printf("Papa sees you working\n");
		}
		int numbers[size-1];
		for(int i = 1; i<size; i++){
			MPI_Irecv(numbers+i, 1, MPI_INT, i, (i*10), MPI_COMM_WORLD, &request);
		}
		MPI_Wait(&request, &status);

		for(int i = 0; i<size-1; i++){
			printf("Recieved Integer %d from processor with rank %d\n", numbers[i], (i+1));
		}
	}else{
		int num = rand();
		MPI_Isend(&num, 1, MPI_INT, 0, rank*10, MPI_COMM_WORLD, &request);

		char buffer[256];
		MPI_Irecv(buffer, 12, MPI_CHAR, 0, rank*10, MPI_COMM_WORLD, &request);

		MPI_Wait(&request, &status);

		printf("Got message from Dr. Park and its just %s\n", buffer);
	}	

	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == rand()%size){
		printf("Everyone Reached the barrier My name is %d\n", rank);

		sleep(3);

		system("clear");
	}	


	MPI_Finalize();
}
