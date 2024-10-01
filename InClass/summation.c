/* Author: Cole Barbes
 * Course: COSC 420 - High Performance Computing - Dr. Jing
 * Purpose: Practice using send and recv either non-blocking or blocking
 * In this program, I use non-blocking mpi recieve and a normal blocking send in the child to
 * Notes: The size of the range is simply the number divided by the size of the world.
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv)
{
	// check for error in number of args
	if(argc < 2){
		return 404;
	}

	MPI_Init(&argc, &argv);

	int size, rank, N;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Request request;
	MPI_Status status;

	// get the N as a n integer
	N = atoi(argv[1]);
	if(N < size){
		if(rank == 0){
			printf("Please enter a number of nodes that is less than or equal to the size of the number you wish to compute. \n More nodes than the target will waste resources!\n");
		}
		return 67;
	}
	
	// find the total size of the boundaries
	int total_size = N/size;

	// if parent
	if(rank == 0){
	
		// start and end: start being the rank times the size of the range to get the beginning number and end is just start + the size 
		int start = rank*total_size+1;
		int end = start + total_size-1;
		
		// sums array
		int sums[size-1];

		// get each element of the array with the recv
		for(int i = 0; i<size-1; i++){
			MPI_Irecv(&sums[i], 1, MPI_INT, MPI_ANY_SOURCE, 50, MPI_COMM_WORLD, &request);
		}

		// first sum
		int sum = 0;
		for(int i = start; i <= end; i++){
			sum=sum+i;
		}

		// wait for the recvs to finish
		MPI_Wait(&request, NULL);
		
		// total sum
		int total = sum;
		for(int i = 0; i<size-1; i++){
			total = total + sums[i];
		}

		// print the result
		printf("The summation from 1 to %d is : %d\n", N, total);  

	}else{
		// get the start and end
		int start = rank*total_size+1;
		int end = start + total_size-1;

		// get the last sum
		if(size == rank+1){
			end = end+(N%size);
		}
		// get the local sum
		int sum = 0;
		for(int i = start; i<= end; i++){
			sum=sum+i;
		}
		// send the result
		MPI_Send(&sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		
	}


	MPI_Finalize();
}
