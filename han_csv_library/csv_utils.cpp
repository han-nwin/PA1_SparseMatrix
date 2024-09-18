#include "csv_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Implementation of exportToCSV function
void exportToCSV(const std::string &filePath, const std::string &element1, const std::string &element2, const std::string &element3) {
    // Open the file in append mode (std::ios::app) to add new data to the end of the file
    std::ofstream file(filePath, std::ios::app);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Could not open or create the file!" << std::endl;
        return;
    }

    // Write the three elements as a comma-separated string to a new line in the file
    file << element1 << "," << element2 << "," << element3 << "\n";

    // Close the file after writing
    file.close();

    std::cout << "Data appended successfully to " << filePath << std::endl;
}

// Implementation of processCSVLine function
int* processCSVLine(const std::string &filePath, int lineNumber) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return nullptr;  // Return nullptr if the file could not be opened
    }

    std::string line;
    int currentLine = 0;
    static int array[ARRAY_SIZE];  // Array to hold elements, size 10 as per your original request
    int idx = 0;  // Index to store elements in the array

    // Read the file line by line until the desired line number is reached
    while (std::getline(file, line)) {
        currentLine++;
        if (currentLine == lineNumber) {
            std::stringstream ss(line);
            std::string element;
            
            // Split the line into elements separated by a comma
            while (std::getline(ss, element, ',')) {
                if (idx < ARRAY_SIZE) {
                    array[idx++] = std::stoi(element);  // Convert each element to int and store in array
                }
            }
            break;  // Stop reading once the desired line is processed
        }
    }

    file.close();

    if (currentLine < lineNumber) {
        std::cerr << "Line number exceeds the total number of lines in the file." << std::endl;
        return nullptr;  // Return nullptr if the line number is out of range
    }

    return array;
}
