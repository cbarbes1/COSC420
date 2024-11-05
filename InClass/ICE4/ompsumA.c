/* Author: Cole Barbes
 * Purpose: sum from 1 to N using 4 threads of execution
 * Creation-data: 10/29/2024
 * Last Edited: 10/29/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char **argv)
{

	// check that sufficient arguments are recieved
	if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	int N = atoi(argv[1]);

	// make sure N is 2000 or above
	if(N < 2000){
		printf("N must be over 2000\n", N);
		exit(2);
	}

	// create a long sum var to get res
	long int sum = 0;

	double start_time = omp_get_wtime(); // get start ttime
	// use omp to thread this loop across 8 threads
	#pragma omp parallel for num_threads(8)
	for(int i = 1; i<=N; i++){
		sum = sum + i;
	}

	// get the end time
	double total_time = omp_get_wtime() - start_time;

	// print the sum and the time it took
	printf("Summation result: %d Run Time: %f\n", sum, total_time);
	return 0;
}
