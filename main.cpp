#include "src/csv_parser.hpp" 
#include "src/statistics.hpp"
#include <iostream>
#include <memory> 

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    CSV_parser csvParser(filename);  // Create an instance of the CSV_parser

    size_t numLines;
    std::cout << "Enter the number of lines to display: ";
    std::cin >> numLines;

    if (csvParser.parseCSV()) {
        csvParser.displayTable(numLines);  // Display the parsed CSV table
    } else {
        std::cerr << "Error parsing CSV file: " << filename << std::endl;
        return 1;
    }

    const CSV_parser::Table csvData = csvParser.getCSVData(); 
    const CSV_parser::Column column = csvData[0];
    StatisticalOperation stats(column, csvData);
    double mean = stats.mean();

    
    return 0;
}