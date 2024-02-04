/********************************************************************************* 
* Harman Gidha
* Main File
* Sparse.c 
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char * argv[])
{
    FILE *in, *out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Error: two arguments needed. Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int n = 0;
    int a = 0;
    int b = 0;
    fscanf(in, "%d", &n);
    fscanf(in, "%d", &a);
    fscanf(in, "%d", &b);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    int i, j;
    double x;
    for(int y = 0; y < a; y++)
    {
        fscanf(in, "%d", &i);
        fscanf(in, "%d", &j);
        fscanf(in, "%lf", &x);
        changeEntry(A, i, j, x);
    }

    for(int y = 0; y < b; y++)
    {
        fscanf(in, "%d", &i);
        fscanf(in, "%d", &j);
        fscanf(in, "%lf", &x);
        changeEntry(B, i, j, x);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix A15 = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, A15);
    fprintf(out, "\n");

    Matrix AB = sum(A , B);
    fprintf(out, "A+B =\n");
    printMatrix(out, AB);
    fprintf(out, "\n");

    Matrix AA = sum(A , A);
    fprintf(out, "A+A =\n");
    printMatrix(out, AA);
    fprintf(out, "\n");

    Matrix BmA = diff(B , A);
    fprintf(out, "B-A =\n");
    printMatrix(out, BmA);
    fprintf(out, "\n");

    Matrix AmA = diff(A , A);
    fprintf(out, "A-A =\n");
    printMatrix(out, AmA);
    fprintf(out, "\n");

    Matrix TA = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, TA);
    fprintf(out, "\n");

    Matrix AtB = product(A , B);
    fprintf(out, "A*B =\n");
    printMatrix(out, AtB);
    fprintf(out, "\n");

    Matrix BtB = product(B , B);
    fprintf(out, "B*B =\n");
    printMatrix(out, BtB);
    fprintf(out, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&A15);
    freeMatrix(&AB);
    freeMatrix(&AA);
    freeMatrix(&BmA);
    freeMatrix(&AmA);
    freeMatrix(&TA);
    freeMatrix(&AtB);
    freeMatrix(&BtB);

    fclose(in);
    fclose(out);

    return 0;
}