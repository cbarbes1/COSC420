#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void task_function(int);

int main() {
    #pragma omp parallel
    {
        // Only one thread creates the tasks
        #pragma omp single
        {
            // Seed the random number generator
            srand(time(NULL));

            // Make and execute as many tasks as there are threads
            for (int i = 0; i < omp_get_num_threads(); i++) {
                #pragma omp task
                // Randomly generate a number between 0 and 99
                task_function(rand() % 100);
            }
        }
        // Wait for all tasks to complete
        #pragma omp taskwait
        printf("Hi, I'm thread %d and I'm done\n", omp_get_thread_num());
    }
    return 0;
}

void task_function(int x) {
    printf("Hi, I'm thread %d and I'm doing task %d\n", omp_get_thread_num(), x);
}