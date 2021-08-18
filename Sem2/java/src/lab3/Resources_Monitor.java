package lab3;//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.Resources_Monitor.java file

import lab3.Lab3;

public class Resources_Monitor {
    int N = Lab3.N;

    private int d;
    private int[] R = new int[N];
    private int[][] MO = new int[N][N];

    public synchronized void set_MO(int[][] MO) {
        this.MO = MO;
    }
    public synchronized int[][] get_MO() {
        return MO;
    }

    public synchronized void set_R(int[] R) {
        this.R = R;
    }
    public synchronized int[] get_R() {
        return R;
    }

    public synchronized void set_d(int d) {
        this.d = d;
    }
    public synchronized int get_d() {
        return d;
    }
}
