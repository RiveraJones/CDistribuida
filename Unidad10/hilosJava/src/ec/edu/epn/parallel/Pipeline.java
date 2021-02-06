package ec.edu.epn.parallel;

import java.util.concurrent.Phaser;

public class Pipeline {

    public static void doWork(int n) {
        try {
            Thread.currentThread().sleep(n);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public static void main (final String [] args) {
        final int n = 100;
        for (int numRun=0; numRun<5; numRun++) {
            System.out.printf("Run %d\n", numRun);
            final Phaser ph1 = new Phaser(1);
            final Phaser ph2 = new Phaser(1);
            Thread t1 = new Thread(() -> {
                for (int i=0; i<n; i++) {
                    doWork(10);
                    ph1.arrive();
                }
            });
            Thread t2 = new Thread(() -> {
                for (int i=0; i<n; i++) {
                    ph1.awaitAdvance(i);
                    doWork(10);
                    ph2.arrive();
                }
            });
            Thread t3 = new Thread(() -> {
                for (int i=0; i<n; i++) {
                    ph2.awaitAdvance(i);
                    doWork(10);
                }
            });

            // Secuencial
            long startTime = System.nanoTime();
            for (int i=0; i<n; i++) {
                doWork(10);
                doWork(10);
                doWork(10);
            }
            long timeInNanos = System.nanoTime() - startTime;
            System.out.printf(" Secuencial completo en %8.3f secs\n", timeInNanos/1e9);

            // Paralelo
            startTime = System.nanoTime();
            t1.start();
            t2.start();
            t3.start();
            try {
                t1.join();
                t2.join();
                t3.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            timeInNanos = System.nanoTime() - startTime;
            System.out.printf(" Paralelo completo en %8.3f secs\n", timeInNanos/1e9);
        }

    }
}
