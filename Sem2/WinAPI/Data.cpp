#include <iostream>
#include "Data.h"

static const int n;
Data::Data(int n_given){
    n = n_given;
}

//F1: d = (A * ((B + C) * (MA * ME)))
int d;//result
int* A, B, C;
int** MA, ME;
void Data::F1_input(int c){
    A = get_vec_with(c);
    B = get_vec_with(c);
    C = get_vec_with(c);
    MA = get_matrix_with(c);
    ME = get_matrix_with(c);
}
void Data::F1_calc(){ //constant for
    int** MD1 = multiply_matrix(MA, ME);
    int* d2 = sum_vec(B, C);
    int* d3 = multiply_vec_matr(d2, MD1);
    d = scalar_multiply_vec(A, d3);

    delete [] d2;
    delete [] d3;
    for (int i = 0; i < n; i++) {
        delete [] MD1[i];
    }
}
int Data::F1_result(){
    delete [] A;
    delete [] B;
    delete [] C;
    for (int i = 0; i < n; i++) {
        delete [] MA[i];
        delete [] ME[i];
    }
    return d;
}
void Data::F1_clean(){
    delete d;
    delete [] A;
    delete [] B;
    delete [] C;
    for (int i = 0; i < n; i++) {
        delete [] MA[i];
        delete [] ME[i];
    }
}

//F2: MG = SORT(MF) * MK + ML
int** MF, MK, ML;
int** MG;
void Data::F2_input(int c){
    MF = get_matrix_with(c);
    MK = get_matrix_with(c);
    ML = get_matrix_with(c);
}
void Data::F2_calc(){
    int** MD1 = sort_matrix(MF);
    int** MD2 = multiply_matrix(MD1, MK);
    MG = sum_matrix(MD2, ML);

    for (int i = 0; i < n; i++) {
        delete [] MD1[i];
        delete [] MD2[i];
    }
}
int** Data::F2_result(){
    return MG;
}
void Data::F2_clean(){
    for (int i = 0; i < n; i++) {
        delete [] MF[i];
        delete [] MK[i];
        delete [] ML[i];
        delete [] MG[i];
    }
}

//F3: O = SORT(R + S) * (MT * MP)
int* R, S, O;
int** MT, MP;
void Data::F3_input(int c){
    R = get_vec_with(c);
    S = get_vec_with(c);
    MT = get_matrix_with(c);
    MP = get_matrix_with(c);
}
void Data::F3_calc(){
    int* D1 = sum_vec(R, S);
    int* D2 = sort_vec(D1);
    int** MD3 = multiply_matrix(MT, MP);
    O = multiply_vec_matr(D2, MD3);

    delete [] D1;
    delete [] D2;
    for (int i = 0; i < n; i++) {
        delete [] MD3[i];
    }
}
int* Data::F3_result(){
    return O;
}
void Data::F3_clean(){
    delete [] R;
    delete [] S;
    delete [] O;
    for (int i = 0; i < n; i++) {
        delete [] MT[i];
        delete [] MP[i];
    }
}

int** Data::multiply_matrix(int** MA, int** MB){
    int** MT = new int[n][n];
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            MT[k][i] = 0;
            for (int j = 0; j < n; j++) {
                MT[k][i] += +MA[k][j] * MB[j][i];
            }
        }
    }
    return MT;
}
int* Data::multiply_vec_matr(int* V, int** MA){
    int m;
    int* R = new int[n];
    for (int i = 0; i < n; i++) {
        m = 0;
        for (int j = 0; j < n; j++) {
            m += V[i] * MA[j][i];
        }
        R[i] = m;
    }
    return R;
}
int* Data::sum_vec(int* A, int* B){
    for (int i = 0; i < n; i++) {
        A[i] += B[i];
    }
    return A;
}
int** Data::sum_matrix(int** MA, int** MB){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MA[i][j] += MB[i][j];
        }
    }
    return MA;
}
int Data::scalar_multiply_vec(int* A, int* B){
    int t = 0;
    for (int i = 0; i < n; i++) {
        t += A[i] + B[i];
    } return t;
}
int** Data::sort_matrix(int** MA) {
    int t;              // temporary
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            for (int k = 1; k < j; k++) {
                if (MA[i][k] < MA[i][k + 1]) {
                    t = MA[i][k];
                    MA[i][k] = MA[i][k + 1];
                    MA[i][k + 1] = t;
                }
            }
        }
    }
    return MA;
}
int* Data::sort_vec(int* V){
    int t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (V[i] > V[j]){
                t = V[j];
                V[j] = V[i];
                V[i] = t;
            }
        }
    }
    return V;
}

int* Data::get_vec_with(int c){
    int* V = new int[n];
    for (int i = 0; i < n; i++) {
        V[i] = c;
    }
    return V;
}
int** Data::get_matrix_with(int c)
{
    int** MA = new int[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MA[i][j] = c;
        }
    }
    return MA;
}