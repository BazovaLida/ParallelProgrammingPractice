//Parallel and distributed computing
//Laboratory work 5
//Variant 28
//MO = (MD * MC) * e + max(Z) * MX
//Bazova Lida
//IV-81
//Date: 30.03.2021
//main.cpp file

#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;


void calculate_MO(int, int, int, int**);
void fillVector(int*);
void fillMatrix(int**);
int max_Z(int);
void outputMatrix();
void createArrays();

const int N = 12;
const int P = 4;
const int H = N / P;
const int c = 2;

int e;
int m = INT_MIN;//minimum int value
int* Z;
int** MX;
int** MC;
int** MD;
int** MO;


int main() {
    cout << "The program is started!\n";
    createArrays();
    int t_id = 0;

#pragma omp parallel num_threads(P) private (t_id) shared (Z, MC, MX, e, c, H)
    {
        int m_i, e_i;
        int** MD_i;

        t_id = omp_get_thread_num();

        cout << "Thread " << t_id + 1 << " started\n";

        switch (t_id) {
            case 0:
                e = c;                      //Введення e
                fillMatrix(MX);             //Введення MX
                break;
            case 2:
                fillMatrix(MC);             //Введення MC
                break;
            case 3:
                fillVector(Z);              //Введення Z
                break;
        }


#pragma omp barrier                          // synchronizing by input Z
        if(t_id == 3)
            fillMatrix(MD);

        m_i = max_Z(t_id * H);              //Обчислення m_i = max(ZH)

#pragma omp critical(CS)  //CS1 - Обчислення m = max(m, mi)
        {
            if (m < m_i)
                m = m_i;
        }

#pragma omp barrier      //очікування обчислення m

#pragma omp critical(CS) //CS2 - копіювання m
        {
            m_i = m;
        }

#pragma omp critical(CS) //CS3 - копіювання e
        {
            e_i = e;
        }

#pragma omp critical(CS) //CS4 - копіювання MD
        {
            MD_i = MD;
        }

        calculate_MO(t_id * H, m_i, e_i, MD_i);// final calculation of MO

#pragma omp barrier     // synchronizing calculation of MO
        if (t_id == 2) {
            outputMatrix();
        }

        cout << "Thread " << t_id + 1 << " is ended\n";
    }
    cout << "The program is ended!\n";
    return 0;
}

void fillVector(int* V){
    for (int i = 0; i < N; i++)
        V[i] = c;
}

void fillMatrix(int** MA){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            MA[i][j] = c;
    }
}

int max_Z(int shift){
    int max = INT_MIN;
    for (int i = shift; i < shift + H; ++i) {
        if(max < Z[i])
            max = Z[i];
    }
    return max;
}

void calculate_MO(int shift, int m_g, int e_g, int** MD_g){
    int** MR = new int* [N];
    for (int i = 0; i < N; i++) {
        MR[i] = new int[N];
        for (int j = 0; j < N; j++) {
            MR[i][j] = 0;
            if (j < H + shift && j >= shift) {
                for (int k = 0; k < N; k++) {
                    MR[i][j] += MD_g[i][k] * MC[k][j];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = shift; j < shift + H; ++j) {
            MO[i][j] = MR[i][j] * e_g + m_g * MX[i][j];
        }
    }
}

void outputMatrix(){
    cout << "Result: MO = {\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << MO[i][j] << "; ";
        }
        cout << "\n";
    }
    cout << "}\n";
}

void createArrays(){
    Z = new int[N];
        MX = new int*[N];
        MC = new int*[N];
        MD = new int*[N];
        MO = new int*[N];    
    for (int i = 0; i < N; ++i)
    {
        MX[i] = new int[N];
        MC[i] = new int[N];
        MD[i] = new int[N];
        MO[i] = new int[N];
        for (int j = 0; j < N; ++j)
        {
            MO[i][j] = 0;
        }
    }
}