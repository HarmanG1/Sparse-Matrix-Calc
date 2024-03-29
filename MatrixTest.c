/********************************************************************************* 
* Harman Gidha
* MatrixTest.c 
*********************************************************************************/ 

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(){
    int n=100000;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H;

    changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
    changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
    changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
    changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
    changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
    changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
    changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
    changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
    changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    C = scalarMult(1.5, A);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");

    D = sum(A, B);
    printf("%d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");

    E = diff(A, A);
    printf("%d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");

    F = transpose(B);
    printf("%d\n", NNZ(F));
    printMatrix(stdout, F);
    printf("\n");

    G = product(B, B);
    printf("%d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");

    H = copy(A);
    printf("%d\n", NNZ(H));
    printMatrix(stdout, H);
    printf("\n");

    printf("%s\n", equals(A, H)?"true":"false" );
    printf("%s\n", equals(A, B)?"true":"false" );
    printf("%s\n", equals(A, A)?"true":"false" );

    makeZero(A);
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);

    Matrix Aa = newMatrix(10);
    printf("reach 1\n");
    changeEntry(Aa, 2, 1, 2);
    changeEntry(Aa, 3, 1, 5);
    changeEntry(Aa, 1, 2, 2);
    changeEntry(Aa, 1, 3, 5);
    changeEntry(Aa, 1, 1, 4);
    changeEntry(Aa, 2, 2, 2);
    printf("reach 2\n");
    changeEntry(Aa, 2, 5, 0);
    changeEntry(Aa, 2, 3, 0);
    changeEntry(Aa, 3, 3, 5);
    changeEntry(Aa, 1, 3, 0);
    changeEntry(Aa, 3, 1, 0);
    changeEntry(Aa, 3, 3, 0);
    printf("reach 3\n");
    changeEntry(Aa, 7, 6, 42);
    printf("reach 3.5\n");
    changeEntry(Aa, 10, 1, 24);
    printf("reach 4\n");
    changeEntry(Aa, 7, 6, 0);
    printf("reach 5\n");
    makeZero(Aa);
    changeEntry(Aa, 5, 5, 5);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&Aa);

    return 0;
}