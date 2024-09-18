#include "csv_utils.h"
#include <iostream>

int main() {
    std::string filePath = "output.csv";  // Path to the CSV file

    // Demonstrate exportToCSV by appending multiple lines to the CSV file
    exportToCSV(filePath, "row1", "col1", "data1");
    exportToCSV(filePath, "row2", "col2", "data2");
    exportToCSV(filePath, "row3", "col3", "data3");

    std::cout << "\n--- CSV Data Exported ---\n";

    // Demonstrate processCSVLine by reading specific lines from the CSV file
    int lineNumber = 2;  // Line to be processed (1-based index)
    int* resultArray = processCSVLine(filePath, lineNumber);

    if (resultArray != nullptr) {
        std::cout << "\nElements on line " << lineNumber << ":\n";
        for (int i = 0; i < ARRAY_SIZE; i++) {
            std::cout << resultArray[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
