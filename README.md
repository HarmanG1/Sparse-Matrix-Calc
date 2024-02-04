# Sparse-Matrix-Calc

The files all come together to create a sparse matrix calculator

## Files

### Sparce.c

FindComponents requires two options for an input and output file and operates on a matrix

- <code>input file</code>: specifies the input file to create the matrix
- <code>output file</code>: specifies the output file.

### Matrix.{c,h}

Contains the source and header files for the Matrix ADT implementation

### List.{c,h}

Contains the source and header files for the Linked list ADT implementation

### ListTest.c

Contains the tests to ensure the function of the List ADT from Graph.c

### MatrixTest.c

Contains the tests to ensure the function of the Matrix ADT from Graph.c

### Makefile

Makefile contains the commands to compile, clean, and leak test the files
