#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <stdbool.h>
#include <string.h>

#include <time.h>
//https://inst.eecs.berkeley.edu/~cs61c/fa12/labs/07/
/* To save you time, we are including all 6 variants of the loop ordering
   as separate functions and then calling them using function pointers.
   The reason for having separate functions that are nearly identical is
   to avoid counting any extraneous processing towards the computation
   time.  This includes I/O accesses (printf) and conditionals (if/switch).
   I/O accesses are slow and conditional/branching statements could
   unfairly bias results (lower cases in switches must run through more
   case statements on each iteration).
*/

// -------------------------------------------------------------------------------
void multMat1(int n, float* A, float* B, float* C) {
    int i, j, k;
    float sum = 0.0;
    /* This is ijk loop order. */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; // C[i][j] += A[i][k] * B[k][j]; (a)Version ij k
        }
}

void multMat2(int n, float* A, float* B, float* C) {
    int i, j, k;
    float r;
    /* This is ikj loop order. */
    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; // (f) Version ikj
        }
}

void multMat3(int n, float* A, float* B, float* C) {
    int i, j, k;
    /* This is jik loop order. */
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += [i][k]*B[k][j]; (b) Version jik
        }

}


void multMat4(int n, float* A, float* B, float* C) {
    int i, j, k;
    /* This is jki loop order. */
    for (j = 0; j < n; j++)
        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; (c) Version jki
        }

}


void multMat5(int n, float* A, float* B, float* C) {
    int i, j, k;
    /* This is kij loop order. */
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];   //C[i][j] += A[i][k]*B[k][j]; (e) Version kij
        }

}

void multMat6(int n, float* A, float* B, float* C) {
    int i, j, k;
    /* This is kji loop order. */
    for (k = 0; k < n; k++)
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];    //C[i][j] += A[i][k]*B[k][j];   (d) Version kji
        }

}
//****************************************************************************************************/
void imprimirMatriz(int n, float* matriz) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", matriz[i * n + j]);
        }
        printf("\n");
    }
}

bool compararMatrices(int n, float* A, float* B) {
    for (int i = 0; i < n * n; i++) {
        if (A[i] != B[i]) {
            printf("Las matrices no son iguales\n");

            return false;

        }
    }

    printf("Las matrices son iguales\n");

    return true;
}


/* defaults to Part 1.  pass it any argument for Part 2. */
/* uses clock() timing features from time.h */

int main(int argc, char** argv) {
    int n_1 = 3; // Tamaño de la matriz

    float A_1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Matriz A
    float B_1[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // Matriz B
    float Expected_1[9] = { 90,114,138,54,69,84,18,24,30 }; //Matriz Expected
    float C_1[9] = { 0 }; // Matriz resultado inicializada en cero


    printf("***PRIMER CASO DE PRUEBA***\n");


    printf("-Algoritmo 3\n");

    multMat3(n_1, A_1, B_1, C_1); 


    compararMatrices(n_1,C_1, Expected_1);

    printf("-Algoritmo 5\n");

    memset(C_1, 0, sizeof(C_1));

    multMat5(n_1, A_1, B_1, C_1);


    compararMatrices(n_1, C_1, Expected_1);

    printf("-Algoritmo 6\n");

    memset(C_1, 0, sizeof(C_1));

    multMat6(n_1, A_1, B_1, C_1);


    compararMatrices(n_1, C_1, Expected_1);


    int n_2 = 2; // Tamaño de la matriz

    float A_2[4] = { 1, 2, 3, 4 }; // Matriz A
    float B_2[4] = { 5, 6, 7, 8 }; // Matriz B
    float Expected_2[4] = { 23, 34, 31, 46 }; // Matriz Expected
    float C_2[4] = { 0 }; // Matriz resultado inicializada en cero

    
    printf("***SEGUNDO CASO DE PRUEBA***\n");


    printf("-Algoritmo 3\n");

    multMat3(n_2, A_2, B_2, C_2);


    compararMatrices(n_2, C_2, Expected_2);


    printf("-Algoritmo 5\n");

    memset(C_2, 0, sizeof(C_2));

    multMat5(n_2, A_2, B_2, C_2);


    compararMatrices(n_2, C_2, Expected_2);

    printf("-Algoritmo 6\n");

    memset(C_2, 0, sizeof(C_2));

    multMat6(n_2, A_2, B_2, C_2);

    compararMatrices(n_2, C_2, Expected_2);



    int n_3 = 4; // Tamaño de la matriz

    float A_3[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }; // Matriz A
    float B_3[16] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // Matriz B
    float Expected_3[16] = { 386,444,502,560,274,316,358,400,162,188,214,240,50,60,70,80}; // Matriz Expected
    float C_3[16] = { 0 }; // Matriz resultado inicializada en cero

    printf("***TERCER CASO DE PRUEBA***\n");


    printf("-Algoritmo 3\n");

    multMat3(n_3, A_3, B_3, C_3);


    compararMatrices(n_3, C_3, Expected_3);


    printf("-Algoritmo 5\n");

    memset(C_3, 0, sizeof(C_3));

    multMat5(n_3, A_3, B_3, C_3);


    compararMatrices(n_3, C_3, Expected_3);

    printf("-Algoritmo 6\n");

    memset(C_3, 0, sizeof(C_3));

    multMat6(n_3, A_3, B_3, C_3);

    compararMatrices(n_3, C_3, Expected_3);

    


    int n_4 = 5; // Tamaño de la matriz

    float A_4[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 }; // Matriz A
    float B_4[25] = { 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // Matriz B
    float Expected_4[25] = {1215,1330,1445,1560,1675,940,1030,1120,1210,1300,665,730,795,860,925,390,430,470,510,550,115,130,145,160,175 }; // Matriz Expected
    float C_4[25] = { 0 }; // Matriz resultado inicializada en cero


    printf("***CUARTO CASO DE PRUEBA***\n");


    printf("-Algoritmo 3\n");

    multMat3(n_4, A_4, B_4, C_4);


    compararMatrices(n_4, C_4, Expected_4);


    printf("-Algoritmo 5\n");

    memset(C_4, 0, sizeof(C_4));

    multMat5(n_4, A_4, B_4, C_4);


    compararMatrices(n_4, C_4, Expected_4);

    printf("-Algoritmo 6\n");

    memset(C_4, 0, sizeof(C_4));

    multMat6(n_4, A_4, B_4, C_4);

    compararMatrices(n_4, C_4, Expected_4);



    int n_5 = 4; // Tamaño de la matriz

    float A_5[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }; // Matriz A
    float B_5[16] = { 4, 3, 2, 1, 8, 7, 6, 5, 12, 11, 10, 9, 16, 15, 14, 13 }; // Matriz B
    float Expected_5[16] = {50,60,70,80,162,188,214,240,274,316,358,400,386,444,502,560}; // Matriz Expected
    float C_5[16] = { 0 }; // Matriz resultado inicializada en cero



    printf("***QUINTO CASO DE PRUEBA***\n");


    printf("-Algoritmo 3\n");

    multMat3(n_5, A_5, B_5, C_5);


    compararMatrices(n_5, C_5, Expected_5);


    printf("-Algoritmo 5\n");

    memset(C_5, 0, sizeof(C_5));

    multMat5(n_5, A_5, B_5, C_5);


    compararMatrices(n_5, C_5, Expected_5);

    printf("-Algoritmo 6\n");

    memset(C_5, 0, sizeof(C_5));

    multMat6(n_5, A_5, B_5, C_5);

    compararMatrices(n_5, C_5, Expected_5);







    return 0;
}