//Parallel and distributed computing
//ПРГ2
//Variant 29
//d = ((A * MB) * (B * (MZ * MR)) + max(Z)
//Bazova Lida
//IV-81
//Date: .04.2021
//prg2.cpp file

#include <mpi.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int calculate_ai(int*, int*, int*, int*, int*);
int vector_max(int*);
int* vector_in();
int* matrix_in();

int N = 900;
int P, H;
int c = 1;

int main(int argc, char** argv) {
    auto start = chrono::steady_clock::now();

    int t_id;

    // Initialize the MPI environment
    MPI_Init(&argc,&argv);
    // Get the number of processes     
    MPI_Comm_size(MPI_COMM_WORLD, &P);
    // Get the rank of the process's rank
    MPI_Comm_rank(MPI_COMM_WORLD, &t_id);
    int last_id = P-1;
    
    // if(t_id == 0)
    	// printf("The program is started\n");
    // printf("Process %d is started\n", t_id);

    MPI_Comm my_comm;
    //Створення графу якщо кількість потоків > 1
    if(P > 1){
    
        int nodes[P];
        int edges[(P - 1) * 2];


        for(int i = 0, k = 1; i < last_id; i++){
        	nodes[i] = i*2 + 1;
            edges[i*2] = k;
            edges[i*2 + 1] = k - 1;
            k++;
        }
        nodes[last_id] = (P - 1) * 2;

    //  MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph)
        MPI_Graph_create(MPI_COMM_WORLD, P, nodes, edges, false, &my_comm);
    }

    H = N / P;
    int a, b, ai, bi;
    int* Z = new int[H];
    int* MB = new int[N*H];
    int* MR = new int[N*H];
    int *MZ, *A, *B, *Z_in, *MB_in, *MR_in;

    if (t_id == 0) {
        //Дії в першому потоці
        //Введення вектору А
        A = vector_in();
        //Введення вектору В
        B = vector_in();
        //Введення матриці MB
        MB_in = matrix_in();
        MZ = new int[N*N];
    }
    if(t_id == last_id){
        //Дії в останньому потоці
        A = new int[N];
        B = new int[N];
        //Введення вектору Z
        Z_in = vector_in();
        //Введення матриці MR
        MR_in = matrix_in();
        //Введення матриці MZ
        MZ = matrix_in();
    } 
    else if(t_id != 0){
        MZ = new int[N*N];
        A = new int[N];
        B = new int[N];
    }

    if(P > 1){
    //Дії для кожного потоку якщо кількість потоків > 1
// MPI_Bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
//MPI_Scatter(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

        //Копіювання MZi = MZ
        MPI_Bcast(MZ, N*N, MPI_INT, last_id, my_comm);
        //Копіювання Ai = A
        MPI_Bcast(A, N, MPI_INT, 0, my_comm);
        //Копіювання Bi = B
        MPI_Bcast(B, N, MPI_INT, 0, my_comm);


        // Розділення та передача частин вектору Z_H, MВ_H, MR_H усім задачам
        MPI_Scatter(Z_in, H, MPI_INT, Z, H, MPI_INT, last_id, my_comm);
        // Розділення та передача частин матриці MВ_H усім задачам
        MPI_Scatter(MB_in, N*H, MPI_INT, MB, N*H, MPI_INT, 0, my_comm);
        // Розділення та передача частин матриці MR_H усім задачам
        MPI_Scatter(MR_in, N*H, MPI_INT, MR, N*H, MPI_INT, last_id, my_comm);
    }


    //Обчислення ai = (A1* MBH) * (B1 * (MZ1 * MRH)
    ai = calculate_ai(A, MB, B, MZ, MR);

    //Обчислення bi = max (ZH)
    bi = vector_max(Z);

    if(P > 1) {
    //Дії для кожного потоку якщо кількість потоків > 1
// MPI_Reduce(void* send_data, void* recv_data, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm communicator)

        //Обчислення    a = sum(ai)  та передача a потоку 0       
        MPI_Reduce(&ai, &a, 1, MPI_INT, MPI_SUM, 0, my_comm);
        
        //Обчислення b = max(bi) та передача b потоку 0
        MPI_Reduce(&bi, &b, 1, MPI_INT, MPI_MAX, 0, my_comm);
    }
    if(t_id == 0){
        //Обрахунок d та виведення результату у першому потоці
        int d = a + b;
        printf("\nresult: d = %d\n", d);
    }

    // printf("Process %d is ended\n", t_id);
    
    if(t_id == 0){
        auto end = chrono::steady_clock::now();
        printf("The program is ended with N = %d; time %ld ms\n", N,
        chrono::duration_cast<chrono::milliseconds>(end - start).count());
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}

int vector_max(int* V){
    int r = INT_MIN;
    for(int i = 0; i < H; i++){
        if(r < V[i])
            r = V[i];
    }
    return r;
}

//ai = (A * MBH) * (B * (MZ * MRH))
int calculate_ai(int* A, int* MB, int* B, int* MZ, int* MR){
    int* MT = new int[N*H];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < H; j++) {
            MT[N*j + i] = 0;
            for (int k = 0; k < N; k++) {
                MT[N*j + i] += MZ[k*N + i] + MR[k + j*N];
            }
        }
    }

    int* V1 = new int[H];
    int* V2 = new int[H];
    int ai = 0;
    for(int i = 0; i < H; i ++){
        V1[i] = 0;
        V2[i] = 0;
        for(int j = 0; j < N; j ++){
            V1[i] += A[j] * MB[N*i + j];
            V2[i] += B[j] * MT[N*i + j];
        }
        ai += V1[i] + V2[i];

    }
    return ai;
}

int* vector_in(){
    int* V = new int[N];
    for (int i = 0; i < N; i++)
        V[i] = c;
    return V;
}

int* matrix_in(){
    int* MA = new int[N*N];
    for (int i = 0; i < N*N; i++)
        MA[i] = c;
    return MA;
}


// Bcast — отправить всем
// Scatter — делит масив на части и раскидывает по задачам(себе и остальным)
// Gather — собирает кусочки масива 
// Reduce — выполняет указаную функцию над данными всех потоков и передаёт всем потокам результат

//Питання
//Чи можна змінювати мову на 3 розділ курсової
//Для варіанту з решіткою можна створити граф (кількість потоків довільна)


