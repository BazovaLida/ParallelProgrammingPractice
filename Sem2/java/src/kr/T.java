package kr;
//Parallel and distributed computing
//ПРГ1
//Variant 29
//d   = ( (A*MB)*(B* (MZ*MR) ) + max (Z)
//Bazova Lida
//IV-81
//Date: 23.03.2020
//Т.java file

import java.util.Arrays;

public class T extends Thread{

    private static final int N = PRG1.N;

    private final int number;

    private final Synchron_Monitor synchM;
    private final Resources_Monitor resM;
    private final DynamicResources_Monitor dynamicResM;

    private static final int[][] MB = new int[N][N];
    private static final int[][] MR = new int[N][N];
    private static final int[] Z = new int[N];

    public T(Synchron_Monitor synch, Resources_Monitor res, DynamicResources_Monitor dynamicRes, int i) {
        number = i;

        synchM = synch;
        resM = res;
        dynamicResM = dynamicRes;
    }

    @Override
    public void run(){
        System.out.println("Process T" + number + " is started!");

        //Введення даних для обчислення першої формули 1. ai = (A * MBH) * (B * (MZ * MRH)
        //Першим потоком
        if(number == 1) {
            resM.set_A(1);
            resM.set_B(1);
            resM.set_MZ(1);
            fill_Matrix(MB, 1);
            fill_Matrix(MR, 1);

            //Сигнал про завершення введення данних для першого обчислення
            synchM.signal_In();
        }
        //Останнім потоком
        if(number == PRG1.P) {
            resM.set_A(2);
            resM.set_B(2);
            resM.set_MZ(2);
            fill_Matrix(MB, 2);
            fill_Matrix(MR, 2);

            //Сигнал про завершення введення данних для першого обчислення
            synchM.signal_In();
        }

        //Введення інших необхідних даних
        //Першим потоком
        if(number == 1)
            fill_vector(Z, 1);

        //Останнім потоком
        if(number == PRG1.P)
            fill_vector(Z, 2);

        //Чекати на введення даних для першого обчислення
        synchM.wait_In();

        //Копіювання A1 = A
        int[] A_i = resM.get_A();

        //Копіювання B1 = B
        int[] B_i = resM.get_B();

        //Копіювання MZ1 = MZ
        int[][] MZ_i = resM.get_MZ();

        //Обчислення a_i = (A * MB_H) * (B * (MZ * MR_H)
        int a_i = function(A_i, B_i, MZ_i);

        //Обчислення a = a + a1
        dynamicResM.put_a(a_i);

        //Обчислення b_i = max(Z_H)
        int b_i = max_Z();

        //Обчислення b = max(b, bi)
        dynamicResM.put_b(b_i);

        //Дія для потоків 2 ... P
        if (number != 1) {
            //Сигнал про завершення обчислень a та b
            synchM.signal_a_b();
        }
        //Дії для першого потоку
        else  {
            //Очікування сигналу про завершення обчислень a та b
            synchM.wait_a_b();

            //Копіювання a1 = a
            int a1 = dynamicResM.get_a();

            //Копіювання b1 = b
            int b1 = dynamicResM.get_b();

            //Обчислення кінцевого результату
            int d = a1 + b1;

            //Виведення результату
            System.out.println("Result: d = " + d);
        }

        System.out.println("Process T" + number + " is finished!");
    }


    public static void fill_Matrix(int[][] MM, int part) {
        int c = PRG1.c;

        if(part == 1) {
            for (int i = 0; i < N / 2; i++)
                Arrays.fill(MM[i], c);
        }
        else{
            for (int i = N / 2; i < N; i++)
                Arrays.fill(MM[i], c);
        }
    }

    public static void fill_vector(int[] V, int part) {
        int c = PRG1.c;

        if (part == 1)
            Arrays.fill(V, 0, N/2, c);
        else
            Arrays.fill(V, N/2, N, c);
    }


    //a_i = (A * MB_H) * (B * (MZ * MR_H)
    private int function(int[] A, int[] B, int[][] MZ){
        int H = PRG1.H;
        int shift = (number - 1) * H;
        int[][] MT = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                MT[i][j] = 0;
                if (j < H + shift && j >= shift) {
                    for (int k = 0; k < N; k++) {
                        MT[i][j] += MZ[i][k] * MR[k][j];
                    }
                }
            }
        }

        int[] V1 = new int[N];
        int[] V2 = new int[N];
        int a = 0;
        for (int i = 0; i < N; i++) {
            V1[i] = 0;
            V2[i] = 0;
            for (int j = 0; j < N; j++) {
                V1[i] += A[i] * MB[j][i];
                V2[i] += B[i] * MT[j][i];
            }
            a += V1[i] + V2[i];
        }
        return a;
    }

    private int max_Z(){
        int H = PRG1.H;
        int result = Integer.MIN_VALUE;

        for (int i = (number - 1) * H; i < H; i++) {
            if(result < Z[i])
                result = Z[i];
        }

        return result;
    }
}
