/********************************************************************************* 
* Harman Gidha
* Matrix.c
*********************************************************************************/ 

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct EntryObj* Entry;

typedef struct EntryObj{
   int col;
   double val;
} EntryObj;

struct MatrixObj{
   int size;
   int nnz;
   List* rows;
} MatrixObj;

Entry newEntry(int c, double v){
   Entry E = malloc(sizeof(EntryObj));
   assert( E!=NULL );
   E->col = c;
   E->val = v;
   return(E);
}

void freeEntry(Entry* pE){
   if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    assert( M!=NULL );
    M->size = n;
    M->nnz = 0;
    M->rows = malloc(sizeof(List) * n);
    assert( M->rows!=NULL );
    for(int i = 0; i < n; i++)
    {
        M->rows[i] = newList();
    }
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM)
{
    if(pM!=NULL && *pM!=NULL) { 
        for(int i = 0; i < (*pM)->size; i++)
        {
            moveFront((*pM)->rows[i]);
            while(index((*pM)->rows[i]) >= 0)
            {
                Entry e = (Entry)get((*pM)->rows[i]);
                freeEntry(&e);
                moveNext((*pM)->rows[i]);
            }
            freeList(&(*pM)->rows[i]);
            (*pM)->rows[i] = NULL;
        }
        free(*pM);
        *pM = NULL;
    }
}

// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
    if(M == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
    if(M == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    if(A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    if(A->size != B->size)
    {
        return 0;
    }
    else if(A->nnz != B->nnz)
    {
        return 0;
    }
    for(int i = 0; i < A->size; i++)
    {
        if(length(A->rows[i]) != length(B->rows[i]))
        {
            return 0;
        }
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while(index(A->rows[i]) >= 0)
        {
            if(((Entry)get(A->rows[i]))->val != ((Entry)get(B->rows[i]))->val)
            {
                return 0;
            }
            else if(((Entry)get(A->rows[i]))->col != ((Entry)get(B->rows[i]))->col)
            {
                return 0;
            }
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
        }
    }
    return 1;
}

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M)
{
    if(M == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < M->size; i++)
    {
        moveFront(M->rows[i]);
        while(index(M->rows[i]) >= 0)
        {
        	Entry e = (Entry)get(M->rows[i]);
        	freeEntry(&e);
            moveNext(M->rows[i]);
        }
        clear(M->rows[i]);
    }
    M->nnz = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
    if(M == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    if(i < 1 || i > size(M))
    {
        fprintf(stderr, "Error: Precondition not met\n");
        exit(EXIT_FAILURE);
    }

    if(j < 1 || j > size(M))
    {
        fprintf(stderr, "Error: Precondition not met\n");
        exit(EXIT_FAILURE);
    }

    int insert = 0;
    if(length(M->rows[i-1]) == 0)
    {
        if(x != 0)
        {
            prepend(M->rows[i-1], newEntry(j, x));
            M->nnz++;
        }
    }
    else
    {
        moveFront(M->rows[i-1]);
        while(index(M->rows[i-1]) >= 0)
        {
            if(((Entry)get(M->rows[i-1]))->col == j)
            {
                if(x == 0)
                {
                    Entry e = (Entry)get(M->rows[i-1]);
                    freeEntry(&e);
                    M->nnz -= 1;
                }
                else
                {
                    ((Entry)get(M->rows[i-1]))->val = x;
                    //M->nnz++;
                }
                insert = 1;
                break;  
            }
            else if(((Entry)get(M->rows[i-1]))->col > j)
            {
                if(x != 0)
                {
                    insertBefore(M->rows[i-1], newEntry(j, x));
                    M->nnz++;
                }
                insert = 1;
                break;
            }
            moveNext(M->rows[i-1]);
        }
        if(!insert)
        {
            if(x != 0)
            {
                append(M->rows[i-1], newEntry(j, x));
                M->nnz++;
            }
        }
    }
}

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
    if(A == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }
    
    Matrix c = newMatrix(A->size);
    c->nnz = A->nnz;
    for(int i = 0; i< c->size; i++)
    {
        moveFront(A->rows[i]);
        while(index(A->rows[i]) >= 0)
        {
            append(c->rows[i], newEntry(((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val)); //Debug:**Could be an issue if it is using the pointer to rather than entry val***
            moveNext(A->rows[i]);
        }
    }
    return c;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
    if(A == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }
    
    Matrix t = newMatrix(A->size);
    t->nnz = A->nnz;
    for(int i = 0; i< t->size; i++)
    {
        moveFront(A->rows[i]);
        while(index(A->rows[i]) >= 0)
        {
            append(t->rows[((Entry)get(A->rows[i]))->col - 1], newEntry(i + 1, ((Entry)get(A->rows[i]))->val));
            moveNext(A->rows[i]);
        }
    }
    return t;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
    if(A == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    Matrix sm;
    if(x == 0)
    {
        sm = newMatrix(A->size);
    }
    else
    {
        sm = newMatrix(A->size);
        sm->nnz = A->nnz;
        for(int i = 0; i< sm->size; i++)
        {
            moveFront(A->rows[i]);
            while(index(A->rows[i]) >= 0)
            {
                append(sm->rows[i], newEntry(((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val * x));
                moveNext(A->rows[i]);
            }
        }
    }
    return sm;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
    if(A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B))
    {
        fprintf(stderr, "Error: Precondition not met\n");
        exit(EXIT_FAILURE);
    }

    if(equals(A, B))
    {
        return scalarMult(2, A);
    }

    Matrix ms = newMatrix(A->size);
    for(int i = 0; i< ms->size; i++)
    {
        moveFront(B->rows[i]);
        moveFront(A->rows[i]);
        while(index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0)
        {
            if(((Entry)get(A->rows[i]))->col > ((Entry)get(B->rows[i]))->col)
            {
                append(ms->rows[i], newEntry(((Entry)get(B->rows[i]))->col, ((Entry)get(B->rows[i]))->val));
                moveNext(B->rows[i]);
                ms->nnz += 1;
            }
            else if(((Entry)get(A->rows[i]))->col < ((Entry)get(B->rows[i]))->col)
            {
                append(ms->rows[i], newEntry(((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val));
                moveNext(A->rows[i]);
                ms->nnz += 1;
            }
            else{
                if(((Entry)get(A->rows[i]))->val + ((Entry)get(B->rows[i]))->val != 0)
                {
                    append(ms->rows[i], newEntry(((Entry)get(B->rows[i]))->col, ((Entry)get(B->rows[i]))->val + ((Entry)get(A->rows[i]))->val));
                    ms->nnz += 1;
                }
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }
        }
            
        while(index(A->rows[i]) >= 0)
        {
            append(ms->rows[i], newEntry(((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val));
            moveNext(A->rows[i]);
            ms->nnz += 1;
        }

        while(index(B->rows[i]) >= 0)
        {
            append(ms->rows[i], newEntry(((Entry)get(B->rows[i]))->col, ((Entry)get(B->rows[i]))->val));
            moveNext(B->rows[i]);
            ms->nnz += 1;
        }
    }

    return ms;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
    Matrix df = scalarMult(-1, B);
    Matrix sd = sum(A, df);
    freeMatrix(&df);
    return sd;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
    if(A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B))
    {
        fprintf(stderr, "Error: Precondition not met\n");
        exit(EXIT_FAILURE);
    }

    Matrix bt = transpose(B);
    Matrix p = newMatrix(A->size);
    for(int i = 0; i< p->size; i++)
    {
        if(length(A->rows[i]) > 0)
        {
            for(int j = 0; j < p->size; j++)
            {
                double mulsum = 0;
                moveFront(bt->rows[j]);
                moveFront(A->rows[i]);
                while(index(A->rows[i]) >= 0 && index(bt->rows[j]) >= 0)
                {
                    if(((Entry)get(A->rows[i]))->col > ((Entry)get(bt->rows[j]))->col)
                    {
                        moveNext(bt->rows[j]);
                    }
                    else if(((Entry)get(A->rows[i]))->col < ((Entry)get(bt->rows[j]))->col)
                    {
                        moveNext(A->rows[i]);
                    }
                    else{
                        mulsum += ((Entry)get(A->rows[i]))->val * ((Entry)get(bt->rows[j]))->val;
                        moveNext(A->rows[i]);
                        moveNext(bt->rows[j]);
                    }
                }
                if(mulsum)
                {
                    append(p->rows[i], newEntry(j + 1, mulsum));
                    p->nnz += 1;
                }
            }
        }
    }
    freeMatrix(&bt);
    return p;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M)
{
    if(M == NULL)
    {
        fprintf(stderr, "Error: Matrix is Null\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < M->size; i++)
    {
        if(length(M->rows[i]))
        {
            fprintf(out, "%d: ", i + 1);
            moveFront(M->rows[i]);
            while(index(M->rows[i]) >= 0)
            {
                fprintf(out, "(%d, %0.1f) ", ((Entry)get(M->rows[i]))->col, ((Entry)get(M->rows[i]))->val);
                moveNext(M->rows[i]);
            }
            fprintf(out, "\n");
        }
    }
}

