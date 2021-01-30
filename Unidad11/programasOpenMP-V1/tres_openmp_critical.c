// En una matriz de N x M enteros entre 1 y 10, contar numero de 3's
// OpenMP con critical para control de concurrencia a c++

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct args {
  int thID;
  int min;
  int max;
} arg;

int **a;
int c = 0;
int N, M, T;

void tres(){
 int i=0;
 int j=0;
  #pragma omp parallel for private(i,j) num_threads(T)
  for (i=0; i<N; i++) {		
    for (j=0; j<M; j++) {
      if (a[i][j] == 3) {
	#pragma omp critical 
        {
	  c+=1;
	}
      }
    }
  }
}

int main (int argc, char *argv[]) {
  struct timeval ts, tf;
  int i, j;
  int cl, fr;
  pthread_t *th;
  arg *args;

  if (argc != 4){printf("USO: %s <dimX> <dimY> <#hilos>\n", argv[0]); exit (1);}

  N = atoi(argv[1]);
  M = atoi(argv[2]);
  T = atoi(argv[3]);

  a = malloc (N * sizeof (int *));
  args = malloc (T * sizeof (arg));
  if (a==NULL || th==NULL || args==NULL) { printf ("Memoria\n"); exit (1);}

  for (i=0; i<N; i++) {
    a[i] = malloc (M * sizeof (int));
    if (a[i] == NULL) { printf ("Memoria\n"); exit (1);}
  }

  srandom (177845);
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      a[i][j] = random() % 10;

  gettimeofday (&ts, NULL);
  tres();
  gettimeofday (&tf, NULL);

  printf ("TRES OpenMP: %d (%f secs)\n", c, ((tf.tv_sec - ts.tv_sec)*1000000u +
          tf.tv_usec - ts.tv_usec)/ 1.e6);
  exit (0);
}

