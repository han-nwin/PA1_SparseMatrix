/**
* CS/SE 3345 - Programming Assignment 1 -
* Lecturer: Andrew Nemec
* Name: Tan Han Nguyen
* NetID: TXN 200004
* Date: September 7, 2024
* Due Date: September 13, 2024
*/ 

#include <iostream>
#include <stdexcept>
#include <fstream>  // For file handling
#include <string>   

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
    unsigned int rowIndex; ///< The row index of the node (for the matrix).
    unsigned int colIndex; ///< The column index of the node (for the matrix).
    Node* nextRow; ///< Pointer to the next node in the same column.
    Node* nextCol; ///< Pointer to the next node in the same row.

    /**
     * @brief Constructs a new Node object.
     *
     * Initializes the node with the specified data, row index, and column index.
     * Pointers are set to nullptr by default.
     *
     * @param int data The value stored in the node.
     * @param int rowIndex The row number of the node in the matrix.
     * @param int colIndex The column number of the node in the matrix.
     */
    Node(int data = 0, unsigned int rowIndex = 0, unsigned int colIndex = 0)
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
    Node* header;  ///< Pointer to the very header node 0:0
    unsigned int numRow;  // Number of rows in the matrix
    unsigned int numCol; // Number of columns in the matrix
    Node** rowHeaders;  // Dynamic Array of pointers that point to row-header nodes
    Node** colHeaders;  // Dynamic Array of pointers that point to column-header nodes


    public:
    /**
     * @brief Constructs a SparseMatrix object.
     *
     * Initializes a sparse matrix of the specified dimension (row x col).
     *
     * @param numRow The number of rows of the matrix
     * @param numCol The number of columns of the matrix
     */
    SparseMatrix(unsigned int numRow = 0, unsigned int numCol = 0) : numRow(numRow), numCol(numCol) {
        header = new Node(0, numRow, numCol); //Create a Top-Left Header node at 0:0 with row and col numbers stored inside rowIndex, colIndex

        // Allocate memory for row and column headers, and initialize each with a placeholder node
        rowHeaders = new Node*[numRow + 1];  // +1 to handle 1-based indexing
        colHeaders = new Node*[numCol + 1];  // +1 to handle 1-based indexing

        // Assign header to be the first element of rowHeaders and colHeaders arrays
        rowHeaders[0] = header;
        colHeaders[0] = header;

        // Giving placeholders some dummy values
        for (int i = 1; i <= numRow; i++) {
            rowHeaders[i] = new Node(0, i, 0);  // Placeholder for each row
            rowHeaders[i]->nextCol = rowHeaders[i];  // Circular: points back to its placeholder node
        }

        for (int j = 1; j <= numCol; j++) {
            colHeaders[j] = new Node(0, 0, j);  // Placeholder for each column
            colHeaders[j]->nextRow = colHeaders[j];  // Circular: points back to itself
        }
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
        // Delete all nodes in each row (excluding the row headers)
        for (int i = 0; i <= numRow; i++) {
            Node* current = rowHeaders[i]->nextCol;
            Node* head = rowHeaders[i]; // The header of the row
            while (current != head) {  // Stop when we return to the header
                Node* nextNode = current->nextCol;
                delete current;
                current = nextNode;
            }
            delete rowHeaders[i]; // Delete the row header itself
        }

        // Delete all nodes in each column (excluding the column headers)
        for (int j = 0; j <= numCol; j++) {
            Node* current = colHeaders[j]->nextRow;
            Node* head = colHeaders[j]; // The header of the column
            while (current != head) {  // Stop when we return to the header
                Node* nextNode = current->nextRow;
                delete current;
                current = nextNode;
            }
            delete colHeaders[j]; // Delete the column header itself
        }

        // Free the arrays of row and column headers
        delete[] rowHeaders;
        delete[] colHeaders;

        // Finally delete the header pointer
        delete header;
    }
   
    /**
     * @brief Displays the entire sparse matrix.
     *
     * This function iterates through the entire matrix and prints the elements.
     * If a node exists for a specific row and column, it prints the node's data.
     * Otherwise, it prints 0 for elements that are not explicitly stored.
     */
    void display();

    /**
     * @brief Returns the row length of the Sparse Matrix.
     *
     * This method returns the row length of the matrix. For example,
     * if the matrix is 10x5, this method will return 10.
     * The method is marked as 'const', guarantees that the state of the matrix is not altered.
     * 
     * @return int: The row length of the matrix.
     */
    int rowLength() const;

    /**
     * @brief Returns the column length of the Sparse Matrix.
     *
     * This method returns the column length of the matrix. For example,
     * if the matrix is 10x5, this method will return 5.
     * The method is marked as 'const', guarantees that the state of the matrix is not altered.
     *
     * @return int: The column length of the matrix.
     */
    int colLength() const;

    /**
     * @brief Accesses the value at the specified row and column in the sparse matrix.
     *
     * This method retrieves the value stored in the matrix at the given row and column.
     * If no value is stored at that position (i.e., the element is 0 in the sparse matrix),
     * it will either return 0 or throw an exception, depending on the implementation.
     * The method is marked as 'const', guarantees that the state of the matrix is not altered.
     *
     * @param int rowIndex The row index of the element to access.
     * @param int colIndex The column index of the element to access.
     * 
     * @return int The value at the specified row and column. Returns 0 if the element is not stored.
     * 
     * @throws std::out_of_range if the rowIndex or colIndex is outside the matrix bounds.
     */
    int access(int rowIndex, int colIndex) const;

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
     * @param int rowIndex The row index of the element to remove.
     * @param int colIndex The column index of the element to remove.
     * 
     * @throws std::out_of_range if the rowIndex or colIndex is outside the matrix bounds.
     * @throws std::invalid_argument if the element at the specified position is zero (no non-zero element to remove).
     */
    void remove(int rowIndex, int colIndex);

    /**
     * @brief Perform addition of two sparse matrices.
     * 
     * This function performs the matrix addition operation on two input sparse matrices, `a` and `b`. 
     * The function returns a new sparse matrix, `c`, which represents the sum of the input matrices. 
     * Matrix addition is only valid when the dimensions of both matrices are the same. If the input 
     * matrices have different dimensions, an exception will be thrown.
     * 
     * The parameters are passed as `const` references to avoid unnecessary copying and to ensure 
     * that the input matrices are not modified by the function, improving both performance and safety.
     * 
     * @param const SparseMatrix & a: A const reference to a SparseMatrix object representing the first matrix to be added. 
     *          Passing by reference avoids copying the matrix, and the const qualifier ensures that 
     *          the matrix is not modified.
     * @param const SparseMatrix & b: A const reference to a SparseMatrix object representing the second matrix to be added. 
     *          Like `a`, this is passed by reference for efficiency and marked const to guarantee 
     *          the matrix is not altered.
     * 
     * @return SparseMatrix The resulting sparse matrix `c` after adding matrix `a` and matrix `b`.
     * 
     * @throws std::invalid_argument If the dimensions of matrices `a` and `b` do not match.
     * @throws std::runtime_error If any other error occurs during the matrix addition process.
     */
    static SparseMatrix matrixAddition(const SparseMatrix & a, const SparseMatrix & b);

};

// Implementation of rowLength method
int SparseMatrix::rowLength() const {
    return this->numRow;
}

// Implementation of colLength method
int SparseMatrix::colLength() const {
    return this->numCol;
}

// Implementation of access method
int SparseMatrix::access(int rowIndex, int colIndex) const {
    // Check for out-of-bounds indices
    if (rowIndex <= 0 || rowIndex > this->numRow || colIndex <= 0 || colIndex > this->numCol) {
        throw std::out_of_range("Row or column index is out of bounds");
    }

    // Start at the row placeholder
    Node* rowNode = this->rowHeaders[rowIndex];  

    // Traverse and find the correct position in the row based on the column index
    while (rowNode->nextCol != this->rowHeaders[rowIndex] && rowNode->nextCol->colIndex < colIndex) {
        rowNode = rowNode->nextCol;
    }

    // If no node exists, return 0
    if (rowNode->nextCol == this->rowHeaders[rowIndex] || rowNode->nextCol->colIndex != colIndex) {
        return 0;
    }

    // Return the data
    return rowNode->nextCol->data;
}

// Implementation of insert method
void SparseMatrix::insert(int data, int rowIndex, int colIndex) {
    // Check for out-of-bounds indices
    if (rowIndex <= 0 || rowIndex > this->numRow || colIndex <= 0 || colIndex > this->numCol) {
        throw std::out_of_range("Row or column index is out of bounds");
    }

    // No need to add zero value
    if (data == 0) {
        return;
    }

    // ===== Insert into the row ===== //
    // Start at the row placeholder
    Node* rowNode = this->rowHeaders[rowIndex];  

    // Traverse and find the correct position in the row based on the column index
    while (rowNode->nextCol != this->rowHeaders[rowIndex] && rowNode->nextCol->colIndex < colIndex) {
        rowNode = rowNode->nextCol;
    }

    // If the node already exists at the position (rowIndex, colIndex), update its data
    if (rowNode->nextCol != this->rowHeaders[rowIndex] && rowNode->nextCol->colIndex == colIndex) {
        rowNode->nextCol->data = data;  // Update the existing node's data
        return;
    }

    // If no node existed, create a new node for the matrix
    Node* newNode = new Node(data, rowIndex, colIndex);

    // Insert the new node into the row
    newNode->nextCol = rowNode->nextCol;  // Link to the next node in the row
    rowNode->nextCol = newNode;  // Link the previous node to the new node

    //=============================================================================================//

    // ===== Insert into the column ===== //
    // Start at the colum placeholder
    Node* colNode = this->colHeaders[colIndex];  

    // Traverse and find the correct position in the column based on the row index
    while (colNode->nextRow != this->colHeaders[colIndex] && colNode->nextRow->rowIndex < rowIndex) {
        colNode = colNode->nextRow;
    }

    // Insert the new node into the column
    newNode->nextRow = colNode->nextRow;  // Link to the next node in the column
    colNode->nextRow = newNode;  // Link the previous node to the new node
}

// Implementation of remove method
void SparseMatrix::remove(int rowIndex, int colIndex) {
    // Check for out-of-bounds indices
    if (rowIndex <= 0 || rowIndex > this->numRow || colIndex <= 0 || colIndex > this->numCol) {
        throw std::out_of_range("Row or column index is out of bounds");
    }

    // ===== Remove from the row =====
    Node* prevRowNode = this->rowHeaders[rowIndex];
    Node* toRemoveRowNode = prevRowNode->nextCol;

    // Traverse and find the node to remove in the row
    while (toRemoveRowNode != this->rowHeaders[rowIndex] && toRemoveRowNode->colIndex < colIndex) {
        prevRowNode = toRemoveRowNode;
        toRemoveRowNode = toRemoveRowNode->nextCol;
    }

    // If the node is found in the row list
    if (toRemoveRowNode != this->rowHeaders[rowIndex] && toRemoveRowNode->colIndex == colIndex) {
        prevRowNode->nextCol = toRemoveRowNode->nextCol;  // Remove node from row
    } else {
        return;  // Node not found
    }

    // ===== Remove from the column =====
    Node* prevColNode = this->colHeaders[colIndex];
    Node* toRemoveColNode = prevColNode->nextRow;

    // Traverse and find the node to remove in the column
    while (toRemoveColNode != this->colHeaders[colIndex] && toRemoveColNode->rowIndex < rowIndex) {
        prevColNode = toRemoveColNode;
        toRemoveColNode = toRemoveColNode->nextRow;
    }

    // If the node is found in the column list
    if (toRemoveColNode != this->colHeaders[colIndex] && toRemoveColNode->rowIndex == rowIndex) {
        prevColNode->nextRow = toRemoveColNode->nextRow;  // Remove node from column
    }

    // Free the memory of the node
    delete toRemoveRowNode;  // Only need to delete once since row and column point to the same node
}

// Implementation of display method
void SparseMatrix::display() {
    // Iterate over each row
    for (int i = 1; i <= numRow; ++i) {
        Node* current = rowHeaders[i]->nextCol;  // Skip the placeholder and start with the first actual node

        // Iterate over each column in this row
        for (int j = 1; j <= numCol; ++j) {
            // If current is not header and it's the correct column, print the data
            if (current != rowHeaders[i] && current->colIndex == j) { 
                std::cout << current->data << " ";
                current = current->nextCol;  // Move to the next node in the row
            } else {
                // Otherwise, print 0 (sparse matrix)
                std::cout << "0 ";
            }
        }
        // Move to the next row after printing all columns in this row
        std::cout << std::endl;
    }
}

// Implementation of matrixAddition method
SparseMatrix SparseMatrix::matrixAddition(const SparseMatrix & a, const SparseMatrix & b) {
    // Check the size
    if (a.colLength() != b.colLength() || a.rowLength() != b.rowLength()) {
        throw std::invalid_argument("Matrices must be equal in size");
    }
    SparseMatrix c(a.rowLength(),a.colLength());
        // Adding elements
    int sum = 0;
    for(int i = 1; i <= c.rowLength(); i++) {
        for(int j = 1; j <= c.numCol; j++) {
            sum = a.access(i,j) + b.access(i,j);
            c.insert(sum,i,j);
        }
    }
    return c;
}




int main(int argc, char* argv[]){
    // Ensure that a file argument is passed
    if (argc != 2) {
        std::cerr << "Usage: Missing file path argument " << argv[0] << " <csv-file-path>" << std::endl;
        return 1;
    }
    // Check if the file path is to a .cvs
    std::string filePath = argv[1];
    size_t dotPosition = filePath.rfind('.');
    if (dotPosition == std::string::npos || filePath.substr(dotPosition) != ".csv") {
        std::cerr << "Error: The input file must be a .csv file." << std::endl;
        return 1;
    }
    
    std::cout << "++++++++++++++++THIS IS A TEST PORTION+++++++++++++++++" << std::endl;
    SparseMatrix m(5,10);
    m.display();
    std::cout << "Add Data" << std::endl;
    for (int i = 1; i<=5; i++){
        for(int j = 1; j<=10; j++){
            m.insert(8,i,j);
        }
    }
    m.display();
    std::cout << "Num Row: " << m.rowLength() <<std::endl;
    std::cout << "Num Col: " << m.colLength() <<std::endl;

    std::cout << "===Insert===" << std::endl;
    int r = 4;
    int c = 7;
    std::cout << "Row index: " << r << std::endl;
    std::cout << "Col index: " << c << std::endl;
    m.insert(77,r,c);
    m.display();
    std::cout << "===Access===" << std::endl;
    std::cout << "Row index: " << r << std::endl;
    std::cout << "Col index: " << c << std::endl;
    std::cout << "Access Data: " << m.access(r,c) << std::endl;

    std::cout << "===Remove===" << std::endl;
    r = 4;
    c = 7;
    std::cout << "Row index: " << r << std::endl;
    std::cout << "Col index: " << c << std::endl;
    m.remove(r,c);
    m.display();

    std::cout << "===Access After Remove===" << std::endl;
    r = 4;
    c = 7;
    std::cout << "Row index: " << r << std::endl;
    std::cout << "Col index: " << c << std::endl;
    std::cout << "Access Data: " << m.access(r,c) << std::endl;

    std::cout << "===Addition===" << std::endl;
    SparseMatrix aMatrix(3,3);
    std::cout << "Add Data" << std::endl;
    for (int i = 1; i<=3; i++){
        for(int j = 1; j<=3; j++){
            aMatrix.insert(3,i,j);
        }
    }
    aMatrix.display();
    SparseMatrix bMatrix(3,3);
    for (int i = 1; i<=3; i++){
        for(int j = 1; j<=3; j++){
            bMatrix.insert(2,i,j);
        }
    }
    bMatrix.display();

    SparseMatrix cMatrix = SparseMatrix::matrixAddition(aMatrix,bMatrix);
    cMatrix.display();
    return 0;
}