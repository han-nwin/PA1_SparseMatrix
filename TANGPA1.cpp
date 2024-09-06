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
    Node* nextRow; ///< Pointer to the next node in the same row.
    Node* nextCol; ///< Pointer to the next node in the same column.

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
    Node(int data = 0, int rowIndex = 0, int colIndex = 0)
        : data{data}, rowIndex{rowIndex}, colIndex{colIndex}, nextRow{nullptr}, nextCol{nullptr} {}
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
    Node header;  ///< Pointer to the head node of the circularly-linked list.
    int numRow;        // Number of rows in the matrix
    int numCol;        // Number of columns in the matrix
    Node** rowHeaders;  // Dynamic Array of pointers that point to row header nodes
    Node** colHeaders;  // Dynamic Array of pointers that point to column header nodes


    public:
    /**
     * @brief Constructs a SparseMatrix object.
     *
     * Initializes a sparse matrix of the specified dimension (row x col).
     *
     * @param numRow The number of rows of the matrix
     * @param numCol The number of columns of the matrix
     */
    SparseMatrix(int numRow = 0, int numCol = 0) : header(0, numRow, numCol), numRow(numRow), numCol(numCol) {//Create a placeholder node at 0:0 with row and col numbers stored inside rowIndex, colIndex
        this->numRow = numRow;
        this->numCol = numCol;
    }

    /**
     * @brief Destructor for the SparseMatrix class.
     *
     * The destructor is responsible for freeing all dynamically allocated memory
     * associated with the sparse matrix. It traverses the matrix to delete
     * all nodes and ensures that no memory leaks occur when the SparseMatrix object
     * is destroyed.
     */
    ~SparseMatrix() {
        // Delete all the row headers and their corresponding nodes.
        for (int i = 0; i <= numRow; i++) {
            Node* current = rowHeaders[i];
            while (current != nullptr) {
                Node* nextNode = current->nextRow;
                delete current;
                current = nextNode;
            }
        }

        // Free the arrays of row and column headers
        delete[] rowHeaders;
        delete[] colHeaders;
    }

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

    /**
     * @brief Accesses the value at the specified row and column in the sparse matrix.
     *
     * This method retrieves the value stored in the matrix at the given row and column.
     * If no value is stored at that position (i.e., the element is 0 in the sparse matrix),
     * it will either return 0 or throw an exception, depending on the implementation.
     *
     * @param rowIndex The row index of the element to access.
     * @param colIndex The column index of the element to access.
     * 
     * @return int The value at the specified row and column. Returns 0 if the element is not stored.
     * 
     * @throws std::out_of_range if the rowIndex or colIndex is outside the matrix bounds.
     */
    int access(int rowIndex, int colIndex);

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

};

//Implementation of rowLength method
int SparseMatrix::rowLength() {
    return this->numRow;
}

//Implementation of colLength method
int SparseMatrix::colLength() {
    return this->numCol;
}

//Implementation of access method


//Implementation of insert method
void SparseMatrix::insert(int data, int rowIndex, int colIndex) {
    // Check for out-of-bounds indices
    if (rowIndex <= 0 || rowIndex > this->numRow || colIndex <= 0 || colIndex > this->numCol) {
        throw std::out_of_range("Row or column index is out of bounds");
    }
     //No need to add zero value
    if (data = 0) {
        return;
    }


    
}

//Implementation of remove method






int main(int argc, char* argv[]){
    std::cout << "This is a main program" << std::endl;
    SparseMatrix m(5,5);
    std::cout << "row " << m.rowLength() <<std::endl;
    std::cout << "col " << m.colLength() <<std::endl;
    return 0;
}