/**
* CS/SE 3345 - Programming Assignment 1 -
* Lecturer: Andrew Nemec
* Name: Tan Han Nguyen
* NetID: TXN 200004
* Date: September 7, 2024
* Due Date: September 13, 2024
*/ 

#include <iostream>

/**
 * @struct Node
 * @brief Represents a node in a circularly-linked list for a sparse matrix.
 *
 * The Node struct holds an integer data value and pointers to the next nodes
 * in the same row and column of the sparse matrix. This allows efficient
 * traversal of non-zero elements in the matrix.
 */
struct Node {
    int data;     ///< The data value stored in the node.
    int rowIndex; ///< The row index of the node (for the matrix).
    int colIndex; ///< The column index of the node (for the matrix).
    Node* rowPtr; ///< Pointer to the next node in the same row.
    Node* colPtr; ///< Pointer to the next node in the same column.

    /**
     * @brief Constructs a new Node object.
     *
     * Initializes the node with the specified data, row index, and column index.
     * Pointers are set to nullptr by default.
     *
     * @param data The value stored in the node.
     * @param rowIndex The row number of the node in the matrix.
     * @param colIndex The column number of the node in the matrix.
     */
    Node(int data = 0, int rowIndex, int colIndex)
        : data{data}, rowIndex{rowIndex}, colIndex{colIndex}, rowPtr{nullptr}, colPtr{nullptr} {}
};


/**
 * @class SparseMatrix
 * @brief Represents a Sparse Matrix using circularly-linked lists.
 *
 * The SparseMatrix class efficiently stores non-zero elements of a matrix using circularly-linked lists.
 * Each non-zero element is represented as a Node, which contains its value, row, and column indices.
 * The matrix is sparse, meaning that most elements are zero, so only non-zero elements are stored.
 * The class supports various matrix operations such as addition, multiplication, transposition, and scalar multiplication.
 */
class SparseMatrix {
    private:
    Node* header = (0, 0, 0);  ///< Pointer to the head node of the circularly-linked list.

    public:
    /**
     * @brief Constructs a SparseMatrix object.
     *
     * Initializes a sparse matrix of the specified dimension (row x col).
     *
     * @param rowNum The number of rows of the matrix
     * @param colNum The number of columns of the matrix
     */
    SparseMatrix(int rowNum = 0, int colNum = 0) {
        header = new Node(0, rowNum, colNum); //Create a placeholder node at row 0, column 0 with row and col numbers.
    }

    /**
     * @brief Adds a non-zero element to the matrix.
     *
     * Inserts a new non-zero element into the matrix at the specified row and column.
     * This method uses the circularly-linked list structure to efficiently store the element.
     *
     * @param data The non-zero value to be added to the matrix.
     * @param rowIndex The row index of the element.
     * @param colIndex The column index of the element.
     * 
     * @throws std::out_of_range if the rowIndex or colIndex is outside the matrix bounds.
     */
    void insert(int data, int rowIndex, int colIndex);

    /**
     * @brief Removes a non-zero element from the sparse matrix at the specified row and column.
     *
     * This function removes the element at the given row and column in the sparse matrix.
     * It throws an exception if the specified element is zero (indicating no non-zero element at that position),
     * or if the row and column indices are out of bounds for the matrix.
     *
     * @param rowIndex The row index of the element to remove.
     * @param colIndex The column index of the element to remove.
     * 
     * @throws std::out_of_range if the rowIndex or colIndex is outside the matrix bounds.
     * @throws std::invalid_argument if the element at the specified position is zero (no non-zero element to remove).
     */
    void remove(int rowIndex, int colIndex);

    /**
     * @brief Returns the row length of the Sparse Matrix.
     *
     * This method returns the row length of the matrix. For example,
     * if the matrix is 10x5, this method will return 10.
     *
     * @return int: The row length of the matrix.
     */
    int rowLength();

    /**
     * @brief Returns the column length of the Sparse Matrix.
     *
     * This method returns the column length of the matrix. For example,
     * if the matrix is 10x5, this method will return 5.
     *
     * @return int: The column length of the matrix.
     */
    int colLength();


};

//Implementation of add method
void SparseMatrix::insert(int data, int rowIndex, int colIndex) {
    // Check for out-of-bounds indices
    if (rowIndex < 0 || rowIndex >= this->header->rowIndex || colIndex < 0 || colIndex >= this->header->colIndex) {
        throw std::out_of_range("Row or column index is out of bounds");
    }
    

}

//Implementation of remove method

//Implementation of size method
int SparseMatrix::rowLength(){
    return this->header->rowIndex;
}




int main(int argc, char* argv[]){
    std::cout << "This is a main program" << std::endl;
    return 0;
}