#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <variant>
#include <optional>
#include <numeric>
#include <cmath>
#include <map>
#include "csv_parser.hpp"



// Base class for statistical operations
class StatisticalOperation {
public:
    StatisticalOperation(const CSV_parser::Column& column, const CSV_parser::Table& data)
    : column(column), data(data) {};
    double mean() const;
    double variance() const;
    std::map<CSV_parser::ColumnField, int> FrequencyCount() const;
    void summary(const std::string& filename) const;

private:
    CSV_parser::Column column; 
    CSV_parser::Table data;   
};

#endif // STATISTICS_HPP