public class Thread_F1 extends Thread {
    public void run(){
        System.out.printf("Thread 1 is started with name %s, priority %d%n", getName(), getPriority());
        try {
            sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        int n = 10;
        int c = 1;
        Data data = new Data(n);
        data.F1_input(c);

        data.F1_calc();

        Thread.yield();
        int d = data.F1_result();
        System.out.printf("\nThread 1 is finished. Result: d = %d%n", d);
    }
}
