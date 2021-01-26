#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_key_t buffer_key;//a traves de esta variable global. Si no
//tendria una vida efimera, Esta en la memoria global de todo el proceso

void buffer_key_destruct (void *value) {
  free(value);
  pthread_setspecific (buffer_key, NULL);
}

char *lookup (void) {
  char *string;

  string = (char *)pthread_getspecific (buffer_key);//cada ilo recupera su storage privado, y en el strring
  if (string == NULL) {
    string = (char *) malloc (32);
    sprintf (string, "Este es el hilo: %ld\n", pthread_self());//el string almacena la cadena la cadena de caracteres
    pthread_setspecific (buffer_key, (void *)string);//se setea en su propia storage con la misma llave pero diferentes storages
  }
  return (string);
}

void *function (void *arg) {//el lazo, lazo infinito, cuando sale, nunca, livelock consume CPU no termina jamas
  while (1) {
    puts (lookup());//lookup
    sleep(1);
  }
  return (0);
}

int main (void) {
  pthread_t th1, th2;
  pthread_key_create (&buffer_key, &buffer_key_destruct);//creo dos hilos k ejecutan la misma funcion. Creamos una mem
  pthread_create (&th1, NULL, &function, NULL);//mientras el hilo se ejecute la variable no desaparecera
  pthread_create (&th2, NULL, &function, NULL);//se inician, no tienen atributos de tam pila ni na, solo se ejecutaran el lazo

  sleep (20);//pasados los 20 seg los hilos se terminan, el hilo principal lo decide
  return EXIT_SUCCESS;
}
