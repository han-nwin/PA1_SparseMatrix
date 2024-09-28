# Sparse Matrix - CS/SE 3345 Programming Assignment 1

This repository contains the source code for **Programming Assignment 1** in **CS/SE 3345**, taught by Lecturer Andrew Nemec. The project implements a **Sparse Matrix** using circularly-linked lists, allowing for efficient storage and manipulation of matrices with a majority of zero elements.

## Project Overview

This assignment focuses on implementing various matrix operations for sparse matrices, where most elements are zeros, and only non-zero elements are stored and manipulated. The sparse matrix operations implemented include:

- **Addition**
- **Multiplication**
- **Transposition**
- **Scalar Multiplication**
- **Insertion** and **Removal** of elements

The matrix is represented using a circularly-linked list, where each non-zero element is a node containing its value, row and column indices, and pointers to the next element in its row and column.

## Project Structure

- **`Node` Struct**: Represents a node in the circularly-linked list that holds matrix data. Each node contains:
  - `data`: the value stored in the matrix.
  - `rowIndex`: the row index of the node.
  - `colIndex`: the column index of the node.
  - `nextRow`: pointer to the next node in the same column.
  - `nextCol`: pointer to the next node in the same row.

- **`SparseMatrix` Class**: Handles the main operations of the sparse matrix. Key features include:
  - **Construction**: Creates a sparse matrix with a specified number of rows and columns.
  - **Matrix Operations**: Supports addition, multiplication, transposition, and scalar multiplication of matrices.
  - **File Export**: Non-zero matrix elements can be exported to a CSV file.
  - **Memory Management**: Properly frees all allocated memory upon matrix destruction.

## Requirements

- **C++ Compiler**: The code is written in C++ and requires a modern C++ compiler.
- **CSV File**: The program expects a CSV file input containing matrix data.

## Usage

To compile and run the program, follow these steps:

1. **Compile the Program**:
   ```bash
   g++ SparseMatrix.cpp -o SparseMatrix
2. **Run the Prgram**:
   ```bash
   ./SparseMatrix <csv-file-path>
  Replace <csv-file-path> with the path to your CSV file containing the matrix data and operation.
  The program expects a single argument, which is the path to a CSV file that contains matrix data and the operation to perform.

# CSV Input Format

The CSV file should follow this format:

- **First Line**: Contains the operation and matrix size, separated by a comma. For example:
  ```
  A,3
  ```

  **Operations**:
  - `A`: Addition
  - `M`: Multiplication
  - `S`: Scalar Multiplication
  - `T`: Transposition

- **Matrix Data**: Subsequent lines contain the matrix elements in the format:
  ```
  rowIndex,columnIndex,value
  ```

- **Separator**: For operations involving two matrices (Addition and Multiplication), include a line with two commas `,,` to separate the data for each matrix.

## Example for Matrix Addition (A):
```
A,3
1,1,2
1,2,0
1,3,4
,,
1,1,1
1,2,3
1,3,0
```

In this example:
- The operation is Addition (`A`), and the matrices are of size 3x3.
- The first matrix has non-zero elements at positions `(1,1)` and `(1,3)`.
- The second matrix data starts after the `,,` separator.

## Features

- **Sparse Matrix Representation**: Uses a circularly-linked list to store non-zero elements.
- **Matrix Operations**: Performs addition, multiplication, transposition, and scalar multiplication.
- **CSV Export**: Exports the resulting matrix to a CSV file.
- **Error Handling**: Ensures correct matrix dimensions before performing operations and checks for valid CSV input.

## Output

After performing the requested matrix operation, the program outputs the resulting matrix to the console and saves it to a new CSV file named `<original-filename>_output.csv`.

### Example Execution

Given a CSV file named `matrix_data.csv` with the following content:

```
A,3
1,1,2
1,3,4
,,
1,1,1
1,3,0
```

### Steps:

1. **Compile**:
   ```
   g++ SparseMatrix.cpp -o SparseMatrix
   ```

2. **Run**:
   ```
   ./SparseMatrix matrix_data.csv
   ```

### Console Output:

```
A 3
=============
2 0 4 
-----------
1 0 0 
---Result---
3 0 4 
Data exported successfully to 'matrix_data_output.csv'
```

### Resulting CSV File:

The file `matrix_data_output.csv` will contain:
```
1,1,3
1,3,4
```

## License

This project is for educational purposes and is part of a programming assignment.

---

**Author**: Tan Han Nguyen  
**NetID**: TXN200004  
**Date**: September 7, 2024  
**Due Date**: September 13, 2024
