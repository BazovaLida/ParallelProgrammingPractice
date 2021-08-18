package kr;
//Parallel and distributed computing
//ПРГ1
//Variant 29
//d   = ( (A*MB)*(B* (MZ*MR) ) + max (Z)
//Bazova Lida
//IV-81
//Date: 23.03.2020
//PRG1.java file

public class PRG1 {
    public static final int N = 900;
    public static final int P = 4;
    public static final int H = N/P;
    public static final int c = 1;

    private static final long createdMillis = System.currentTimeMillis();

    public static void main(String[] args) throws InterruptedException {
        System.out.println("Main thread is started");

        Synchron_Monitor synch = new Synchron_Monitor();
        Resources_Monitor res = new Resources_Monitor();
        DynamicResources_Monitor dynamicRes = new DynamicResources_Monitor();

        Thread[] threads = new T[P];

        for (int i = 1; i < P + 1; i++) {
            threads[i] = new T(synch, res, dynamicRes, i);
            threads[i].start();
        }

        for (Thread currThread : threads)
            currThread.join();

        int programTime = (int)(System.currentTimeMillis() - createdMillis);
        System.out.println("Time: " + programTime);

        System.out.println("Main thread is finished");
    }
}
