/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Author: C++ameron Vinson                                //
//                                 Creation Date: 10/29/2024                               //
//                                  Last Update: 11/05/2024                                //
//                                                                                         //
//                           If you are not Cameron or Dr. Jing,                           //
//                         close this file and directory immediately!                      //
//                Do not copy and paste this code.  Do your HW on your own.                //
//                                                                                         //
//            Description: Inserts and counts nodes less than 0.5 sequentially.            //
//                                                                                         //
//                                   User Interface: None                                  //
//                                                                                         //
//                                        Notes: None                                      //
/////////////////////////////////////////////////////////////////////////////////////////////

// #include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BT.h"

int main(int argc, char** argv) {
    srand(time(0));

    double t1 = omp_get_wtime();

    Tree tree;

    BTConstructions(&tree);

    Data car;
    car.model = "F-150";
    car.price = 20000;
    car.dealer = "Ford";
    car.color = "Black";
    car.year_make = 2023;

    for (int i = 0; i < 10; i++) { // 1048576
        car.id = i;
        insertNode(&tree, car);
    }

    print(&tree, 4, 0);
    printf("Height: %d\n", height(&tree));
    printf("Number of nodes: %d\n", count(&tree));

    printf("\n");

    balance(&tree);

    print(&tree, 4, 0);
    printf("Height: %d\n", height(&tree));
    printf("Number of nodes: %d\n", count(&tree));

    double t2 = omp_get_wtime();
    double duration = t2-t1;

    printf("Run time: %4.5fs\n", duration); // Return the time it took.

    BTFree(&tree);
    
    return 0;
}
