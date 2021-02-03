#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int max = atoi(argv[1]);
int sum_shared = 0;

#pragma omp parallel for num_threads(4)
    for (int i = 0; i < max; ++i){
      int n = omp_get_num_threads();
      int id  = omp_get_thread_num();
      #pragma omp critical
        sum_shared += i;//todos intentan actualizarla
        printf("Hilo %d con sum_shared =%d\n", id, sum_shared);
    }
printf("---------------%d\n\n", sum_shared);

return 0;
}
