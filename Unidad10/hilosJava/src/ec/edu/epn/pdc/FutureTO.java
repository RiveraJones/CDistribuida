package ec.edu.epn.pdc;

import java.util.concurrent.*;

public class FutureTO {
    public static void main (String argvs[]) throws InterruptedException, ExecutionException, TimeoutException {
        ExecutorService executor = Executors.newFixedThreadPool(1);

        Future<Integer> future = executor.submit(() -> {
            try {
                TimeUnit.SECONDS.sleep(1);
                return 123;
            }
            catch (InterruptedException e) {
                throw new IllegalStateException("task interrupted", e);
            }
        });
        System.out.printf("future: %d\n", future.get(2, TimeUnit.SECONDS));//error xk el future no esta disponible con 1 segundo. Pero con 2 funciona, max te espero 2 segundos.
        //Si no espero lo suficiente voy a tener errores. Max en 2 segundos, se produce despues de 1 segundo.
        executor.shutdownNow();//terminar las tareas en ejecucion o esperando
    }
}
