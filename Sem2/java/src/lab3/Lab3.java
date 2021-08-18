package lab3;
//Parallel and distributed computing
//Laboratory work 3
//Variant 20
//X = (B*Z)*(d*Z + R*(MO*MR))
//Bazova Lida
//IV-81
//Date: 16.03.2021
//lab3.Lab3.java file

import java.util.Arrays;

public class Lab3 {
    public static final int N = 20;
    public static final int H = N/4;
    public static final int c = 1;

    public static int[] B = new int[N];
    public static int[] Z = new int[N];
    public static int[] X = new int[N];
    public static int[][] MR = new int[N][N];


    public static void main(String[] args) {
        System.out.println("Main thread is started");

        Synchronisation_Monitor synch = new Synchronisation_Monitor();
        Resources_Monitor res = new Resources_Monitor();

        Thread t1 = new T1(synch, res);
        Thread t2 = new T2(synch, res);
        Thread t3 = new T3(synch, res);
        Thread t4 = new T4(synch, res);

        t1.start();
        t2.start();
        t3.start();
        t4.start();

        System.out.println("Main thread is finished");
    }

    public static int[][] getNewMatrix(){
        int[][] MA = new int[N][N];
        for (int[] ints : MA) {
            Arrays.fill(ints, c);
        }
        return MA;
    }

    public static int[] getNewVector(){
        int[] V = new int[N];
        Arrays.fill(V, c);
        return V;
    }

    public static void function(int shift, int a, int d, int[] R, int[][] MO){
        int[][] MT = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                MT[i][j] = 0;
                if (j < H + shift && j >= shift) {
                    for (int k = 0; k < N; k++) {
                        MT[i][j] += MO[i][k] * MR[k][j];
                        }
                    }
                }
            }

        int[] V = new int[N];
        for (int i = 0; i < N; i++) {
            V[i] = 0;
            for (int j = 0; j < N; j++) {
                V[i] += R[i] * MT[j][i];
            }
        }

        for (int i = shift; i < H + shift; i++) {
            X[i] = a * (d * Z[i] + R[i]);
        }
    }
}

