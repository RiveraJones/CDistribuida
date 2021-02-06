#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void doWork(int n) {
  //printf("hola\n");
  sleep(n);
}

int main(int argc, char const *argv[]) {

  int n = 1;
  for (int numRun=0; numRun<5; numRun++) {

    printf("Run: %d\n", numRun);
    /* SECUENCIAL-------------------------------------------*/
    clock_t st;
    st = clock();
    for (int i=0; i<n; i++) {
        doWork(1);
        doWork(1);
        doWork(1);
    }
    st = clock() - st;
    double secuencial_time = ((double)st)/(CLOCKS_PER_SEC/1000);
    printf(" Secuencial completo en %f ms\n", secuencial_time);
    /*SECUENCIAL-------------------------------------------*/

    /*PARALELO-------------------------------------------*/

    clock_t pt;
    pt = clock();
    #pragma omp parallel num_threads(3)
    {
      #pragma omp for
      for (int i=0; i<n; i++){
          doWork(1);
        }//barrera implicita

      #pragma omp for
      for (int i=0; i<n; i++){
          doWork(1);
        }//barrera implicita

      #pragma omp for
      for (int i=0; i<n; i++){
          doWork(1);
        }//barrera implicita

    }//barrera implicita
    pt = clock() - pt;
    double parallel_time = ((double)pt)/(CLOCKS_PER_SEC/1000);
    printf(" Paralelo   completo en %f ms\n", parallel_time);
    /*PARALELO-------------------------------------------*/
  }

return 0;
}
