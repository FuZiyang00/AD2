#include "csv_parser.hpp"
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include <algorithm>  // for std::max
#include <cctype>

bool CSV_parser::isNumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c) && c != '.' && c != '-') {
            return false;
        }
    }
    return true;
}


std::vector<std::string> CSV_parser::tokenize(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

bool CSV_parser::parseCSV() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::vector<std::vector<std::string>> rows; // vector of rows

    while (std::getline(file, line)) {
        // read lines and splits based on the comma
        std::vector<std::string> cells = tokenize(line, ',');
        // Process each column and convert to appropriate type
        rows.push_back(cells);
    }

    size_t n_columns = rows.empty() ? 0 : rows[0].size();
    for (size_t i = 0; i < n_columns; ++i) {
        Column column;
        for (const auto& row : rows) {
            const auto& cell = (i < row.size()) ? row[i] : "";
            if (cell.empty()) {
                column.push_back(std::nullopt);
            } else if (isNumeric(cell)) {
                // Numeric field
                try {
                    if (cell.find('.') != std::string::npos) {
                        // Double
                        column.push_back(std::stod(cell));
                    } else {
                        // Integer
                        column.push_back(std::stoi(cell));
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error converting cell to numeric value: " << e.what() << std::endl;
                    // Handle the error (e.g., push a default value or std::nullopt)
                    column.push_back(std::nullopt);
                }
            } else {
                // Categorical data
                column.push_back(cell);
            }
        }
        csv.push_back(column);
    }
    file.close();
    return true;
}

void CSV_parser::displayTable(size_t numLinesToDisplay) const {
    // Vector to store the maximum width for each column
    std::vector<size_t> columnWidths(csv.size(), 0);
    // Calculate maximum width for each column
    for (size_t i = 0; i < csv.size(); ++i) {
        for (size_t j = 0; j < std::min(numLinesToDisplay, csv[i].size()); ++j) {
            if (csv[i][j].has_value()) {
                std::visit([&columnWidths, i](const auto& val) {
                    using T = std::decay_t<decltype(val)>;
                    size_t valueWidth = 0;

                    if constexpr (std::is_same_v<T, std::string>) {
                        valueWidth = val.length();
                    } else {
                        valueWidth = std::to_string(val).length();
                    }

                    columnWidths[i] = std::max(columnWidths[i], valueWidth);
                }, csv[i][j].value());
            } else {
                columnWidths[i] = std::max(columnWidths[i], static_cast<size_t>(2)); // Minimum width for "NA"
            }
        }
    }
    // Iterate over rows
    for (size_t row = 0; row < numLinesToDisplay; ++row) {
        // Iterate over columns
        for (size_t col = 0; col < csv.size(); ++col) {
            if (row < csv[col].size()) {
                if (csv[col][row].has_value()) {
                    std::visit([&columnWidths, col](const auto& val) {
                        std::cout << std::setw(columnWidths[col]) << val;
                    }, csv[col][row].value());
                } else {
                    std::cout << std::setw(columnWidths[col]) << "NA";
                }
            }
            // Add a separator between columns
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}