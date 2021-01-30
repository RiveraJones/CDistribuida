package ec.edu.epn.pdc;

import java.util.concurrent.*;

public class ExecutorCallable {
    public static void main (String argvs[]) throws ExecutionException, InterruptedException {
        Callable<Integer> task = () -> {
            try {
                System.out.printf("Trying to sleep...\n");
                TimeUnit.SECONDS.sleep(1);//nos retorna cuando? despues de 1 sgundo
                return 123;
            }
            catch (InterruptedException e) {
                throw new IllegalStateException("task interrupted", e);
            }
        };
        ExecutorService executor = Executors.newFixedThreadPool(1);//pool de 1 hilo
        Future<Integer> future = executor.submit(task);
        System.out.println("future done? " + future.isDone());//el hilo del pool esta durmiendo.
        Integer result = future.get();//se sincroniza?
        System.out.println("future done? " + future.isDone());//el valor 123 ya esta disponible. Despues de haber sincronzado el pool con el hilo
        //mientras tareas estan ejecutandose en el pool, otros pueden continuar si hay valores disponibles.
        System.out.print("result: " + result);
        //executor.shutdownNow();
    }
}
