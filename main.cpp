#include "src/csv_parser.hpp" 
#include "src/statistics.hpp"
#include <iostream>
#include <memory> 
#include <map>

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
    const CSV_parser::Column salary = csvData[5];
    StatisticalOperation stats(salary, csvData);
    double mean = stats.mean();
    double variance = stats.variance();
    std::map<CSV_parser::ColumnField, int> dictionary = stats.FrequencyCount();
    
    std::cout << "Mean: " << mean << std::endl; 
    std::cout << "Variance: " << variance << std::endl; 
    std::cout << "Frequency map of the column's elements:"<< std::endl <<dictionary<< std::endl;

    return 0;
}
