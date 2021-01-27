package ec.edu.epn.pdc;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.StampedLock;
import static ec.edu.epn.pdc.ConcurrentUtils.sleep;
import static ec.edu.epn.pdc.ConcurrentUtils.stop;

public class OptimisticLocks {
    public static void main (String argvs[]) {
        ExecutorService executor = Executors.newFixedThreadPool(2);//pool de 2 hilos
        StampedLock lock = new StampedLock();//

        executor.submit(() -> {
            //sleep(2);
            long stamp = lock.tryOptimisticRead();//locks hw
            try {
                System.out.println("Optimistic Lock Valid: " + lock.validate(stamp));//con el metodo valido, ese dato que lei nadie lo ha modificado
                sleep(1);                                                   //por lo tanto puedo usarlo. No uso locks
                System.out.println("Optimistic Lock Valid: " + lock.validate(stamp));//valido para hacer la transaccion
                sleep(2);
                System.out.println("Optimistic Lock Valid: " + lock.validate(stamp));//
            } finally {
                lock.unlock(stamp);
            }
        });
        executor.submit(() -> {
            sleep(4);

            long stamp = lock.writeLock();//leo sin pedir una restriccion

            try {
                System.out.println("Write Lock acquired");//hago mis operaciones, nadie mas puede escribir.
                sleep(2);
            } finally {
                lock.unlock(stamp);
                System.out.println("Write done");
            }
        });
        stop(executor);

        //Optimistic Lock Valid: true, la variable stamp no ha sido modificada aun.
        //Write Lock acquired, el hilo consigue el lock de write
        //Optimistic Lock Valid: false, la variable stamp ha sido mdificada y por lo tanto no es valida
        //Write done, el hilo 2 ya ha terminado de escribir
        //Optimistic Lock Valid: false, la variable stamp ha sido modificada y por lo tanto no es valida

        //sleep 4 en el segundo hilo el cual escribe
        //Optimistic Lock Valid: true, la variable stamp no ha sido modificada aun.
        //Optimistic Lock Valid: true, la variable stamp no ha sido modificada aun.
        //Optimistic Lock Valid: true, la variable stamp no ha sido modificada aun.
        //Write Lock acquired, el hilo consigue el lock de write
        //Write done, el hilo 2 ya ha terminado de escribir

        //sleep(2); en el primer hilo, que comprueba si comp ha sido mod. EL segundo obtendra el lock primero, haciendo que
        //ninguno sea valido
        //Write Lock acquired
        //Write done
        //Optimistic Lock Valid: false
        //Optimistic Lock Valid: false
        //Optimistic Lock Valid: false


    }
}
