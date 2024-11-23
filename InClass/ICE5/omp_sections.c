#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int storage = 0;
    int hello = 444;
    int sum = 0;
    int first = 5345;
    #pragma omp parallel
    {
        // Define sections to be executed by different threads
        #pragma omp sections private(storage) firstprivate(first) lastprivate(hello) reduction(+:sum) nowait
        {
            #pragma omp section
            {

                storage = rand()%100;
                hello = storage;
                
                // Randomly generate a number between 0 and 99
                int random_number = rand() % 100;
                printf("Hi, I'm thread %d and I'm doing section %d => private %d => lastprivate %d => %d\n", omp_get_thread_num(), random_number, storage, hello, first);
                first = hello;

                sum +=1;
            }

            #pragma omp section
            {
                storage = rand()%100;
                hello = storage;
                // Randomly generate a number between 0 and 99
                int random_number = rand() % 100;
                printf("Hi, I'm thread %d and I'm doing section %d => private %d => lastprivate %d => %d\n", omp_get_thread_num(), random_number, storage, hello, first);

                sum+=1;
            }


            #pragma omp section 
            {
                storage = rand()%100;
                hello = storage;
                // Randomly generate a number between 0 and 99
                int random_number = rand() % 100;
                printf("Hi, I'm thread %d and I'm doing section %d => private %d => lastprivate %d => %d\n", omp_get_thread_num(), random_number, storage, hello,first);
                sum+=1;
            }
        }
    }
    printf("The value of 'hello' after the parallel region is %d\n", hello);
    printf("The value of 'first' after the parallel region is %d\n", first);
    printf("The value of 'sum' after the parallel region is %d\n", sum);

    return 0;
}