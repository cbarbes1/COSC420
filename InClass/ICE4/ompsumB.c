/* Author: Cole Barbes
 * Purpose: sum numbers from 1 to N 
 * Creation date: 10/29/2024
 * Last Edited: 10/29/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char **argv)
{
	// check if sufficient args was given
	if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}

	// get the n
	int N = atoi(argv[1]);

	// make sure n is 2000 or above
	if(N < 2000){
		printf("N must be over 2000\n", N);
		exit(2);
	}

	// sum var
	long int sum = 0;

	// get start time
	double start_time = omp_get_wtime();
	// use omp to split loop accross 4 threads
	#pragma omp parallel for num_threads(8)
	for(int i = 1; i<=N; i++){
		// this section is the critical section
		#pragma omp critical
		{
			sum = sum + i;
		}
	}

	// get end time
	double total_time = omp_get_wtime() - start_time;

	// print the sum and the runtime
	printf("Summation result: %d Runtime: %fs\n", sum, total_time);
	return 0;
}
