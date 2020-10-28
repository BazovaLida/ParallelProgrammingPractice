public class Lab2 {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("The program is started");

        Thread thr1 = new Thread_F1();
        thr1.setPriority(1);
        thr1.setName("Thread for function 1");
        thr1.start();

        Thread thr2 = new Thread_F2();
        thr2.setPriority(2);
        thr2.setName("Thread for function 2");
        thr2.start();

        Thread thr3 = new Thread_F3();
        thr3.setPriority(9);
        thr3.setName("Thread for function 3");
        thr3.start();

        thr1.join();
        thr2.join();
        thr3.join();

        System.out.println("\nThread with main function is finished");
    }
}