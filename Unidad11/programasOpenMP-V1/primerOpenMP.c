#include <stdio.h>
#include <omp.h>
//gcc -o primerOpenMP -fopenmp primerOpenMP.c

int  main(void) {
  /* code */
  #pragma omp parallel
  //pragma omp parallel num_threads(5)
  {
    printf("Hello from thread ? of ?.\n");
  }
  return 0;
}
