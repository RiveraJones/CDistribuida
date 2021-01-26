// book - fig 6.1

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int sz, row, col;
  double (*MA)[10], (*MB)[10], (*MC)[10];
} matrix_type_t;

void *thread_mult (void *w) {
  matrix_type_t *work = (matrix_type_t *)w;
  int i, r=work->row, c=work->col;
  work->MC[r][c] = 0;
  for (i=0; i<work->sz; i++)
    work->MC[r][c] += work->MA[r][i] * work->MB[i][c];
  return NULL;
}

int main (int argc, char *argv[]) {
  int i, row, col, sz = 10;
  double MA[10][10], MB[10][10], MC[10][10];
  matrix_type_t *work;
  pthread_t th[10*10];

  srandom (613);
  for (row=0; row<sz; row++)
    for (col=0; col<sz; col++) {
      MA[row][col] = (double)(random() % 100);
      MB[row][col] = (double)(random() % 100);
    }
  printf ("MAX_TH = %ld\n", sysconf (__STDC_NO_THREADS__));

  for (row=0; row<sz; row++)
    for (col=0; col<sz; col++) {
      work = (matrix_type_t *)malloc (sizeof(matrix_type_t));
      work->sz = sz;
      work->row = row;
      work->col = col;
      work->MA=MA; work->MB=MB; work->MC=MC;
      pthread_create (&(th[col + row*10]), NULL, thread_mult, (void *)work);//cada uno va a calcular la fila y columna que le corresponde
    }

  for (i=0; i<sz*sz; i++)
    pthread_join(th[i], NULL);//necesito coordinar, los 100 hilos ya han terminado y luego se desp[liega]
    //el hilo padre sepa que todos han terminado para saber el resultado
  for (row=0; row<sz; row++){
    for (col=0; col<sz; col++)
      printf ("%9.3lf ", MC[row][col]);
    printf("\n");
  }
}
