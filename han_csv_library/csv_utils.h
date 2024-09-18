#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>

// Define a constant for the array size (you can change this as needed)
const int ARRAY_SIZE = 10;

/**
 * @brief Exports three elements as a comma-separated string into a CSV file.
 * 
 * If the file already exists, it appends the new data to a new line. If the file doesn't exist, 
 * it creates the file and writes the data.
 * 
 * @param filePath The path to the CSV file.
 * @param element1 The first element to export.
 * @param element2 The second element to export.
 * @param element3 The third element to export.
 */
void exportToCSV(const std::string &filePath, const std::string &element1, const std::string &element2, const std::string &element3);

/**
 * @brief Reads a specific line from a CSV file and returns the elements as an array.
 * 
 * @param filePath The path to the CSV file.
 * @param lineNumber The line number to read (1-based index).
 * @return int* An array of elements from the specified line in the CSV.
 */
int* processCSVLine(const std::string &filePath, int lineNumber);

#endif  // CSV_UTILS_H