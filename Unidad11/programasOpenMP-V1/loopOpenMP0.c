#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int max = atoi(argv[1]);
int sum_shared = 0;

clock_t t;
t = clock();
#pragma omp parallel num_threads(4)
{
    int sum_local=0;
    #pragma omp for nowait
    for (int i = 0; i < max; ++i) {
      //#pragma omp critical
        sum_local += i;
    }
    //seccion critica de codigo
    sum_shared += sum_local;
}//barrera implicita
t = clock() - t;
double time_taken = ((double)t)/(CLOCKS_PER_SEC/1000);
printf("\ntiempo %f mss \n", time_taken);
printf("---------------%d\n\n", sum_shared);

return 0;
}
