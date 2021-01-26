// maxthreads.c -  maximo numero de hilos

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int c = 0;
pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;

void *thread1 (void *not_used) {
  printf ("Tid del hilo thread1(): %ld\n", pthread_self());//imprime el ID
  pthread_mutex_lock(&mt);//creamos un acceso excluso a la vsariable global, protegiendola con un mutex
  c++;//se ejecutara secuancielmente, para preservar la integridad de esta variable.ya no paralel
  pthread_mutex_unlock(&mt);
}

int main (int argc, char *argv[]) {//en cualquier pila, se va a iniciar un hilo. Este hilo controla el num de argumentos
  pthread_t *th;
  int i, t, n;

  if (argc != 2) {printf ("USO: %s <num-hilos>\n", argv[0]); exit (1);}
  printf ("MAX THs: %d\n", _SC_THREAD_THREADS_MAX);
  printf ("Tid del hilo main(): %ld\n", pthread_self());//imprime el identificador del hilo inicial
  n = atoi(argv[1]);//n es el numero de hilos adicionales que queremos crear
  th = (pthread_t *) malloc (sizeof(pthread_t) * n);//creamos los n hilos

  for (i=0; i<n; i++) {//para cada hilo devolvelos su identificador
    t = pthread_create (&th[i], NULL, thread1, NULL);
    if (t==0)
      printf ("TH (%d): %ld\n", i, th[i]);
    else {
      printf ("t: %d\n", t);
      break;
    }
  }
  for (i=0; i<n; i++)
    pthread_join (th[i], NULL);//el hilo inicial, el hilo padre tiene la resp de ejcutar el JOIN
    //me asguro que todos los hilos han actualizado y han finalizado, linea 38
  printf ("C = %d\n", c);//c se incrementa correctamente
}
//programas que creen hilos hasta que te devuelva el mensaje de que yasta,
//constante simbolica.
