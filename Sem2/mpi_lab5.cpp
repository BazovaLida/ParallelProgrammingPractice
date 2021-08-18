//Parallel and distributed computing
//Laboratory work 5                     mpi - посилання повідомлень
//Variant 18
//MX = (B*Z)*(MZ*MM) - (MR*MC)*d 
//Bazova Lida
//IV-81
//Date: 13.04.2021
//lab5.cpp file

// execute:
// mpic++ -o lab5 lab5.cpp
// mpirun -np 6 ./lab5


#include <mpi.h>
#include <stdio.h>
using namespace std;


int* calculate_MX(int, int*, int*, int*, int*, int);
int mulVectors(int*, int*);
int* vector_in();
int* matrix_in();
void matrix_out(int*, int);

int N = 18;
int P, H;
int c = 3;

int main(int argc, char** argv) {

    int t_id;
    int tag = 0;

    // Initialize the MPI environment
    MPI_Init(&argc,&argv);
    // Get the number of processes     
    MPI_Comm_size(MPI_COMM_WORLD, &P);
    // Get the rank of the process's rank
    MPI_Comm_rank(MPI_COMM_WORLD, &t_id);

    MPI_Comm my_comm;
    int nodes[P] = {5, 6, 7, 8, 9, 10};//накопичувальна сумма ребер
    int edges[10] = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
//  MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph)
    MPI_Graph_create(MPI_COMM_WORLD, P, nodes, edges, false, &my_comm);


    printf("Process %d is started\n", t_id);


    H = N / P;
    int d, a, ai;
    int* B = new int[H];
    int* Z = new int[H];
    int *MZ, *MR, *MC_in, *B_in, *Z_in, *MM_in, *MX_out;
    int* MM = new int[N*H];
    int* MC = new int[H*N];
    int* MX = new int[N*H];

    if (t_id == 0) {
        MR = new int[N*N];
        //Введення B, Z, MZ, MM
        B_in = vector_in();
        Z_in = vector_in();
        MZ = matrix_in();
        MM_in = matrix_in();

        //Прийняти d, від задачі Т6
        MPI_Recv(&d, 1, MPI_INT, 5, tag, my_comm, MPI_STATUS_IGNORE);
        printf("%d received: d = %d\n", t_id, d);
        //Передати  d задачам Т2-Т5
        for(int i = 1; i < P; i++)
            MPI_Send(&d, 1, MPI_INT, i, tag, my_comm);


    } else if(t_id == 5) {
        MZ = new int[N*N];
        MX_out = new int[N*N];
        //Введення d, MR, MC
        d = c;
        MR = matrix_in();
        MC_in = matrix_in();

        //Передати  d задачі Т1
        MPI_Send(&d, 1, MPI_INT, 0, tag, my_comm);


    } else{
        MR = new int[N*N];
        MZ = new int[N*N];

        MPI_Recv(&d, 1, MPI_INT, 0, tag, my_comm, MPI_STATUS_IGNORE);
    }


    // Передати  MR, MC_H  задачам Т1-T5
    // Передати  B_H, Z_H, MC_H, MZ  задачам Т2-T6
// MPI_Bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
    MPI_Bcast(MR, N*N, MPI_INT, 5, my_comm);
    MPI_Bcast(MZ, N*N, MPI_INT, 0, my_comm);

//MPI_Scatter(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
    MPI_Scatter(MC_in, N*H, MPI_INT, MC, N*H, MPI_INT, 5, my_comm);
    MPI_Scatter(B_in, H, MPI_INT, B, H, MPI_INT, 0, my_comm);
    MPI_Scatter(Z_in, H, MPI_INT, Z, H, MPI_INT, 0, my_comm);
    MPI_Scatter(MM_in, N*H, MPI_INT, MM, N*H, MPI_INT, 0, my_comm);

    // Обчислити ai = (BH * ZH)
    ai = mulVectors(B, Z);
    printf("T%d: ai = %d\n", t_id, ai);

    //Обчислення    a = a1 + a2 + a3 + a4 + a5 + a6  та передача a усім потокам      
// MPI_Allreduce(void* send_data, void* recv_data, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm communicator)
    MPI_Allreduce(&ai, &a, 1, MPI_INT, MPI_SUM, my_comm);


    //Обчислення    MX1 = a*(MZ*MMH) - (MR*MCH)*d  
    MX = calculate_MX(a, MZ, MM, MR, MC, d);


    //Передати  MX1 - MX5  задачі Т6 (через задачі Т1 для задач Т2-Т5)
//MPI_Gather(void* send_data, int send_count, MPI_Datatype send_datatype, void* recv_data, int recv_count, MPI_Datatype recv_datatype, int root, MPI_Comm communicator)
    MPI_Gather(MX, N*H, MPI_INT, MX_out, N*H, MPI_INT, 5, my_comm);


    if(t_id == 5)
            matrix_out(MX_out, N*N);

    printf("Process %d is ended\n", t_id);

    // Finalize the MPI environment.
    MPI_Finalize();
}

int mulVectors(int* V1, int* V2){
    int r = 0;
    for(int i = 0; i < H; i++){
        r += V1[i] * V2[i];
    }
    return r;
}

//MXi = a*(MZ*MMH) - (MR*MCH)*d  
int* calculate_MX(int a, int* MZ, int* MM, int* MR, int* MC, int d){
    int* MX = new int[N*H];

    int* MT1 = new int[N*H];
    int* MT2 = new int[N*H];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < H; j++) {
            MT1[N*j + i] = 0;
            MT2[N*j + i] = 0;

            for (int k = 0; k < N; k++) {
                MT1[N*j + i] += MZ[k*N + i] + MM[k + j*N];
                MT2[N*j + i] += MR[k*N + i] + MM[k + j*N];
            }
            MX[i + N*j] = a*MT1[i + N*j] - d*MT2[i + N*j];
        }
    }
    return MX;
}

void matrix_out(int* MX, int size){
    printf("Result: MX = {");
    for (int n = 0; n < size; ++n) {
        if((n % N) == 0)
            printf("\n");
        printf("%d ", MX[n]);
    }
    printf("}\n");
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