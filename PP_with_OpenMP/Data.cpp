#include <iostream>
#include "Data.h"

int n;
Data::Data(int n_given) {
    Data::n = n_given;
}

//F1: d = (A * ((B + C) * (MA * ME)))
int d;//result
int* A, B, C;
int** MA, ME;
void Data::F1_input(int c) {
    A = get_vec_with(c);
    B = get_vec_with(c);
    C = get_vec_with(c);
    MA = get_matrix_with(c);
    ME = get_matrix_with(c);
}
void Data::F1_calc() { //constant for
    int** MM = multiply_matrix(MA, ME);
    B = sum_vec(B, C);
    int* V = multiply_vec_matr(B, MM);
    d = scalar_multiply_vec(A, V);

    delete[] V;
    for (int i = 0; i < n; i++) {
        delete[] MM[i];
    }
}
int Data::F1_result() {
    return d;
}
void Data::F1_clean() {
    delete[] A;
    delete[] B;
    delete[] C;
    for (int i = 0; i < n; i++) {
        delete[] MA[i];
        delete[] ME[i];
    }
}

//F2: MG = SORT(MF) * MK + ML
int** MF, MK, ML;
int** MG;
void Data::F2_input(int c) {
    MF = get_matrix_with(c);
    MK = get_matrix_with(c);
    ML = get_matrix_with(c);
}
void Data::F2_calc() {
    MF = sort_matrix(MF);
    int** MM = multiply_matrix(MF, MK);
    MG = sum_matrix(MM, ML);
}
int** Data::F2_result() {
    return MG;
}
void Data::F2_clean() {
    for (int i = 0; i < n; i++) {
        delete[] MF[i];
        delete[] MK[i];
        delete[] ML[i];
        delete[] MG[i];
    }
}

//F3: O = SORT(R + S) * (MT * MP)
int* R, S, O;
int** MT, MP;
void Data::F3_input(int c) {
    R = get_vec_with(c);
    S = get_vec_with(c);
    MT = get_matrix_with(c);
    MP = get_matrix_with(c);
}
void Data::F3_calc() {
    int* V = sum_vec(R, S);
    V = sort_vec(V);
    int** MM = multiply_matrix(MT, MP);
    O = multiply_vec_matr(V, MM);

    for (int i = 0; i < n; i++) {
        delete[] MM[i];
    }
}
int* Data::F3_result() {
    return O;
}
void Data::F3_clean() {
    delete[] R;
    delete[] S;
    delete[] O;
    for (int i = 0; i < n; i++) {
        delete[] MT[i];
        delete[] MP[i];
    }
}

int** Data::multiply_matrix(int** MM1, int** MM2) {
    int** MM = new int* [n];
    for (int k = 0; k < n; k++) {
        MM[k] = new int[n];
        for (int i = 0; i < n; i++) {
            MM[k][i] = 0;
            for (int j = 0; j < n; j++) {
                MM[k][i] += MM1[k][j] * MM2[j][i];
            }
        }
    }
    return MM;
}
int* Data::multiply_vec_matr(int* V, int** MM) {
    int m;
    int* r = new int[n];
    for (int i = 0; i < n; i++) {
        m = 0;
        for (int j = 0; j < n; j++) {
            m += V[i] * MM[j][i];
        }
        r[i] = m;
    }
    return r;
}
int* Data::sum_vec(int* V1, int* V2) {
    for (int i = 0; i < n; i++) {
        V1[i] += V2[i];
    }
    return V1;
}
int** Data::sum_matrix(int** MM1, int** MM2) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MM1[i][j] += MM2[i][j];
        }
    }
    return MM1;
}
int Data::scalar_multiply_vec(int* V1, int* V2) {
    int t = 0;
    for (int i = 0; i < n; i++) {
        t += V1[i] + V2[i];
    } return t;
}
int** Data::sort_matrix(int** MM) {
    int t;              // temporary
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            for (int k = 1; k < j; k++) {
                if (MM[i][k] < MM[i][k + 1]) {
                    t = MM[i][k];
                    MM[i][k] = MM[i][k + 1];
                    MM[i][k + 1] = t;
                }
            }
        }
    }
    return MM;
}
int* Data::sort_vec(int* V) {
    int t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (V[i] > V[j]) {
                t = V[j];
                V[j] = V[i];
                V[i] = t;
            }
        }
    }
    return V;
}

int* Data::get_vec_with(int c) {
    int* V = new int[n];
    for (int i = 0; i < n; i++) {
        V[i] = c;
    }
    return V;
}
int** Data::get_matrix_with(int c)
{
    int** MM= new int* [n];
    for (int i = 0; i < n; i++) {
        MM[i] = new int[n];
        for (int j = 0; j < n; j++) {
            MM[i][j] = c;
        }
    }
    return MM;
}

void Data::print_matrix(int** MM) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << MM[i][j] << " ";
        } std::cout << ";" << std::endl;
    } std::cout << "}" << std::endl;
}
void Data::print_vector(int* V) {
    for (int i = 0; i < n; ++i) {
        std::cout << V[i] << " ";
    }
    std::cout << "}" << std::endl;
}