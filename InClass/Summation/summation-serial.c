#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

	if (argc < 2){
		return 404;
	}

	int N = atoi(argv[1]);
	int sum = 0;

	for(int i = 1; i<=N; i++){
		sum = sum + i;
	}

	printf("The sum from 1 to %d is %d\n", N, sum);
	return 0;
}
