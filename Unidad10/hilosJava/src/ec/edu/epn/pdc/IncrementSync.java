package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class IncrementSync {
    private static int count = 0;

    void increment() {
        count = count + 1;
    }
    synchronized void incrementSync() {
        count = count + 1;
    }
    void incrementSyncBk() {//sincronizo todo el bloque
        synchronized (this) {
            count = count + 1;
        }
    }
    public static void main(String argvs[]) {
        IncrementSync inc = new IncrementSync();
        ExecutorService executor = Executors.newFixedThreadPool(1);//pool con 1 hilo

        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::increment));
        //sleep (2);// se ejecuta el hilo del pool secuencialmente los 10000 incrementos ejecutado por un pool de 1 solo hilo y  el hilo principal, le espere al hilo principal
        System.out.println(count);//que metodo para hacer que se sincronicen, para saber que hayan terminado y continuar. Join no.
        count = 0;
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::incrementSync));
        //sleep (2);//con un pool de 2 hilos, 5000 tareas en cada hilo. COMO DEBO SINCRONIZAR AL HILO PRINCIPAL CON LOS HILOS DEL POOL, PARA IMPRIMIR CORRECTAMENTE CUANDO LOS HILOS HAYAN FINALIZADO LAS 10000
        System.out.println(count);//EL HILO PRINCIPAL DEBE ESPERAR A QUE LOS HILOS TERMINEN PARA IMPRIMIR CORRECTAMENTE
        count = 0;
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(inc::incrementSyncBk));
        stop(executor);
        System.out.println(count);
    }
}