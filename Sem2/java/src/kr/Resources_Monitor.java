package kr;
//Parallel and distributed computing
//ПРГ1
//Variant 29
//d   = ( (A*MB)*(B* (MZ*MR) ) + max (Z)
//Bazova Lida
//IV-81
//Date: 23.03.2020
//Resources_Monitor.java file

import java.util.Arrays;

public class Resources_Monitor {
    private static final int N = PRG1.N;

    private final int[] A = new int[N];
    private final int[] B = new int[N];
    private final int[][] MZ = new int[N][N];

    public synchronized void set_MZ(int part) {
        T.fill_Matrix(MZ, part);
    }
    public synchronized int[][] get_MZ() {
        return Arrays.copyOf(MZ, MZ.length);
    }

    public synchronized void set_A(int part) {
        T.fill_vector(A, part);
    }
    public synchronized int[] get_A() {
        return Arrays.copyOf(A, A.length);
    }

    public synchronized void set_B(int part) {
        T.fill_vector(B, part);
    }
    public synchronized int[] get_B() {
        return Arrays.copyOf(B, B.length);
    }
}
