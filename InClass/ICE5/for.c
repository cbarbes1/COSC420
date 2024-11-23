#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main()
{
    srand(time(0));
    omp_set_num_threads(8);

    // reduction using * operator
    int sum = 1;
    #pragma omp parallel for reduction(*:sum)
    for(int i = 1; i<=16; i++){
        sum = sum*2;
    }

    printf("%d\n", sum);

    int number = 1000;
    int sharedvar = 100;
    int other;
    int hello = 4444;
    int yes = 55;
    // shared 
    #pragma omp parallel for default(private) shared(sharedvar) private(other) firstprivate(hello) lastprivate(yes)
    for(int i = 0; i<8; i++){
        printf("This is thread number %d and my info is: \n", omp_get_thread_num());
        printf("The first private was %d\n", hello);
        
        hello = i;
        yes = i;
        printf("The last private was %d\n", yes);
        other = rand()%100;
        #pragma omp critical
        {
            sharedvar = sharedvar+1;
            number = number+1;
        }
        printf("%d\n", sharedvar);
        printf("%d\n", number);
        printf("My private variable is %d\n", other);

        other = other *i;
        printf("after i add stuff %d\n", other);

        

        printf("The first private was set to %d\n", hello);

        printf("The last private was set to %d\n", yes);
        
    }


    // ordered
    #pragma omp parallel for ordered
    for(int i = 0; i < 16; i++){
        #pragma omp ordered
        {
            printf("we run in order thread_id: %d\n", omp_get_thread_num());
        }
    }

    // scheduled 
    // static
    printf("static:\n");
    #pragma omp parallel for schedule(static, 2) num_threads(8)
    for(int i = 0; i < 16; i++){
        printf("We run on 8 threads always index: %d, thread_id: %d\n", i, omp_get_thread_num());
    }

    // dynamic
    printf("dynamic:\n");
    #pragma omp parallel for schedule(dynamic, 2) num_threads(8)
    for(int i = 0; i < 16; i++){
        printf("We run on 8 threads always index: %d, thread_id: %d\n", i, omp_get_thread_num());
    }

    // guided
    printf("guided:\n");
    #pragma omp parallel for schedule(guided, 2) num_threads(8)
    for(int i = 0; i < 16; i++){
        printf("We run on 8 threads always index: %d, thread_id: %d\n", i, omp_get_thread_num());
    }

    return 0;
}