#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <variant>
#include <optional>

class CSV_parser {
public:
    using ColumnField = std::variant<int, double, std::string>;
    using Column = std::vector<std::optional<ColumnField>>;
    using Table = std::vector<Column>;
    
    CSV_parser(const std::string& filename) : filename(filename), csv() {};
    
    // functions 
    bool parseCSV();
    void displayTable(size_t numLinesToDisplay) const; 
    const Table& getCSVData() const { return csv; }

private: 
    std::string filename;
    Table csv;
    // Function to split a string into tokens based on a delimiter
    std::vector<std::string> tokenize(const std::string& str, char delimiter) const;
};
#endif // CSV_PARSER_HPP