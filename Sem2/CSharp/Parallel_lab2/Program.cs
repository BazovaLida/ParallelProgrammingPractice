//Parallel and distributed computing
//Laboratory work 2
//"Semaphores, mutexes, events, critical sections"
//Variant 26
//V = sort(d*B + Z*MM) * (MX*MT)
//Bazova Lida
//IV-81
//Date: 02.03.2021
//Lab2.cs file

using System;
using System.Threading;

namespace Parallel_lab2
{
    internal class Program
    {
        private const int N = 8;
        private const int P = 4;
        private const int H = N/P;
        private const int c = 2;

        private static int d;
        
        private static int[] B = new int[N];
        private static int[] V = new int[N];
        private static int[] Z = new int[N];

        private static int[,] MX = new int[N, N];
        private static int[,] MM = new int[N, N];
        private static int[,] MT = new int[N, N];
        
        private static Object CS1 = new object();
        private static Object CS2 = new object();
        private static Mutex mutex;
        private static Semaphore S_MX;

        private static Semaphore S234_1;
        private static Semaphore S134_1;
        private static Semaphore S123_1;
        private static Semaphore[] S_V = new Semaphore[3];
        
        private static EventWaitHandle E234_2;
        private static EventWaitHandle E1_1;
        private static EventWaitHandle E1_2;
        private static EventWaitHandle E2_2;

        private static int[] A = new int[N];
        private static int[] A_H3 = new int[H];
        private static int[] A_H4 = new int[H];
        private static int[] A_2H2 = new int[2 * H];

        public static void Main(string[] args)
        {
            Console.WriteLine("The program is started");

            mutex = new Mutex(false);
            
            S_MX = new Semaphore(1, 1);
            S234_1 = new Semaphore(0, 3);
            S134_1 = new Semaphore(0, 3);
            S123_1 = new Semaphore(0, 3);
            S_V[0] = new Semaphore(0, 1);
            S_V[1] = new Semaphore(0, 1);
            S_V[2] = new Semaphore(0, 1);

            E234_2 = new ManualResetEvent(false);
            E1_1 = new ManualResetEvent(false);
            E1_2 = new ManualResetEvent(false);
            E2_2 = new ManualResetEvent(false);
            
            Thread t1 = new Thread(T1);
            Thread t2 = new Thread(T2);
            Thread t3 = new Thread(T3);
            Thread t4 = new Thread(T4);
            
            t1.Start();
            t2.Start();
            t3.Start();
            t4.Start();
            
            Console.WriteLine("\nThe program is finished");
        }

        private static void T1()
        {
            Console.WriteLine("T1 is started\n");
            // 1  	Введення MM
            MM = makeMatrix(MM);
            // 2  	Введення B
            B = makeVector(B);
            // 3  	Сигнал задачам Т2, Т3, Т4 про введення B та ММ
            S234_1.Release(3);
            // 4  	Введення MX
            MX = makeMatrix(MX);
            // 5  	Чекати на введення Z у задачі Т2 та d у задачі Т4
            S134_1.WaitOne();
            S123_1.WaitOne();
            // 6  	Копіювання d1 = d
            mutex.WaitOne();
            int d1 = d;
            mutex.ReleaseMutex();
            // 7  	Копіювання Z1 = Z
            int[] Z1;
            lock (CS1)
            {
                Z1 = Z;
            }
            
            // 8  	Обчислення AH1 = sort(d1 * BH + Z1*MMH)
            int[] A_H1 = calculateAH(d1, Z1, 0);
            Array.Sort(A_H1);
            // 9  	Чекати на завершення обчислень АН3 у задачі Т3
            E1_1.WaitOne();
            // 10  	Обчислення А2н1 = merge_sort(AH1, AH3)
            int[] A_2H1 = merge_sort(A_H1, A_H3);
            // 11  	Чекати на завершення обчислень А2Н2 у задачі Т2
            E1_2.WaitOne();
            // 12  	Обчислення А = sort(A2H1, A2H2)
            A = merge_sort(A_2H1, A_2H2);
            // 13  	Сигнал задачам Т2, Т3, Т4 про завершення обчислень А
            E234_2.Set();
            
            // 14  	Копіювання A1 = A
            int[] A1;
            lock (CS2)
            {
                A1 = A;
            }
            // 15  	Копіювання MX1 = MX
            S_MX.WaitOne();
            int[,] MX1 = MX;
            S_MX.Release();
            // 16  	Обчислення V = A1*(MX1*MT_H)
            calculateV(A1, MX1, 0);
            // 17  	Сигнал задачі Т2 про завершення обчислень VH1
            S_V[0].Release();
            Console.WriteLine("T1 is finished\n");
        }
        
        private static void T2()
        {
            Console.WriteLine("T2 is started\n");
            
            // 1  	Введення Z
            Z = makeVector(Z);
            // 2  	Сигнал задачам Т1, Т3, Т4 про введення Z
            S134_1.Release(3);
            // 3  	Чекати на введення B та ММ у задачі Т1 та d у задачі Т4
            S234_1.WaitOne();
            S123_1.WaitOne();
            // 4  	Копіювання d2 = d
            mutex.WaitOne();
            int d2 = d;
            mutex.ReleaseMutex();
            // 5  	Копіювання Z2 = Z
            int[] Z2;
            lock (CS1)
            {
                Z2 = Z;
            }
            
            // 6  	Обчислення AH2 = sort(d2 * BH + Z2*MMH)
            int[] A_H2 = calculateAH(d2, Z2, H);
            Array.Sort(A_H2);
            // 7  	Чекати на завершення обчислень АН4 у задачі Т4
            E2_2.WaitOne();
            // 8  	Обчислення А2н2 = merge _sort (AH2, AH4)
            A_2H2 = merge_sort(A_H2, A_H4);
            // 9  	Сигнал задачі Т1 про завершення обчислень A2Н2
            E1_2.Set();
            // 10  	Чекати на завершення обчислень А у задачі Т1
            E234_2.WaitOne();
            
            // 11  	Копіювання A2 = A
            int[] A2;
            lock (CS2)
            {
                A2 = A;
            }
            // 12  	Копіювання MX2 = MX
            S_MX.WaitOne();
            int[,] MX2 = MX;
            S_MX.Release();
            // 13  	Обчислення V = A2*(MX2*MTH)
            calculateV(A2, MX2, H);
            // 14  	Чекати на завершення обчислень V в задачах Т1, Т3, Т4
            S_V[0].WaitOne();
            S_V[1].WaitOne();
            S_V[2].WaitOne();
            // 15  	Виведення результату V
            Console.WriteLine("V = {");
            for (int i = 0; i < N; i++)
            {
                Console.WriteLine(V[i] + ", ");
            }
            Console.WriteLine("}\n");
            Console.WriteLine("T2 is finished\n");
        }
        
        private static void T3()
        {
            Console.WriteLine("T3 is started\n");
            // 1  	Чекати на введення B та ММ у задачі Т1, Z у задачі Т2 та d у задачі Т4
            S234_1.WaitOne();
            S134_1.WaitOne();
            S123_1.WaitOne();
            // 2  	Копіювання d3 = d
            mutex.WaitOne();
            int d3 = d;
            mutex.ReleaseMutex();
            // 3  	Копіювання Z3 = Z
            int[] Z3;
            lock (CS1)
            {
                Z3 = Z;
            }
            
            // 4  	Обчислення AH3 = sort(d3 * BH + Z3*MMH)
            A_H3 = calculateAH(d3, Z3, H*2);
            Array.Sort(A_H3);
            // 5  	Сигнал задачі Т1 про завершення обчислень AH3
            E1_1.Set();
            
            // 6  	Чекати на завершення обчислень А у задачі Т1
            E234_2.WaitOne();
            // 7  	Копіювання A3 = A
            int[] A3;
            lock (CS2)
            {
                A3 = A;
            }
            // 8  	Копіювання MX3 = MX
            S_MX.WaitOne();
            int[,] MX3 = MX;
            S_MX.Release();
            // 9  	Обчислення V = A3*(MX3*MTH)
            calculateV(A3, MX3, H*2);
            // 10  	Сигнал задачі Т2 про завершення обчислень V
            S_V[1].Release();
            Console.WriteLine("T3 is finished\n");
        }
        
        private static void T4()
        {
            Console.WriteLine("T4 is started\n");
            // 1  	Введення d
            d = c;
            // 2  	Сигнал задачам Т1, Т2, Т4 про введення d
            S123_1.Release(3);
            // 3  	Введення MT
            MT = makeMatrix(MT);
            // 4  	Чекати на введення B та ММ у задачі Т1 та Z у задачі Т2
            S234_1.WaitOne();
            S134_1.WaitOne();
            
            // 5  	Копіювання d4 = d
            mutex.WaitOne();
            int d4 = d;
            mutex.ReleaseMutex();
            // 6  	Копіювання Z4 = Z
            int[] Z4;
            lock (CS1)
            {
                Z4 = Z;
            }
            // 7  	Обчислення AH4 = sort(d4 * BH + Z4*MMH)
            A_H4 = calculateAH(d4, Z4, H*3);
            Array.Sort(A_H4);
            // 8  	Сигнал задачі Т2 про завершення обчислень AH4
            E2_2.Set();
            
            // 9  	Чекати на завершення обчислень А у задачі Т1
            E234_2.WaitOne();
            // 10  	Копіювання A4 = A
            int[] A4;
            lock (CS2)
            {
                A4 = A;
            }
            // 11  	Копіювання MX4 = MX
            S_MX.WaitOne();
            int[,] MX4 = MX;
            S_MX.Release();
            // 12  	Обчислення V = A4*(MX4*MTH)
            calculateV(A4, MX4, H*3);
            // 13  	Сигнал задачі Т2 про завершення обчислень V
            S_V[2].Release();
            Console.WriteLine("T4 is finished\n");
        }

        private static void calculateV(int[] A_given, int[,] MX_given, int shift)
        {
            int[,] MR = new int[N, N];
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    MR[i, j] = 0;
                    if (j < H + shift && j >= shift)
                    {
                        for (int k = 0; k < N; k++)
                        {
                            MR[i, j] += MX_given[i, k] * MT[k, j];
                        }
                    }
                }
            }
            // int[] r = new int[N];
                for (int i = shift; i < H + shift; i++)
                {
                    V[i] = 0; 
                    for (int j = 0; j < N; j++)
                    {
                        V[i] += A_given[j] * MR[j, i];
                    }
                }
        }
        private static int[] merge_sort(int[] V1, int[] V2)
        {
            int[] V_res = new int[V1.Length * 2]; 
            for (int i = 0; i < V_res.Length; i++)
            {
                if (i < V1.Length)
                    V_res[i] = V1[i];
                else V_res[i] = V2[i - V2.Length];
            }
            Array.Sort(V_res);
            return V_res;
        }
        private static int[] calculateAH(int d_given, int[] Z_given, int shift)
        {
            int[] V1 = new int[H];
            int[] V2 = new int[H];
            for (int i = 0; i < H; i++)
            {
                V1[i] = d_given * B[i];
                V2[i] = 0; 
                for (int j = 0; j < N; j++)
                {
                    V2[i] += Z_given[j] * MM[i, j];
                }
                V1[i] = V1[i] + V2[i];
            }

            return V1;
        }
        private static int[,] makeMatrix(int[,] matrix) {
            for (var i = 0; i < N; i++)
            {
                for (var j = 0; j < N; j++) 
                {
                    matrix[i, j] = c;
                }
            }
            return matrix;
        }
        private static int[] makeVector(int[] vector) {
            for (var i = 0; i < N; i++)
            {
                vector[i] = c;
            }
            return vector;
        }
    }
}