#include "statistics.hpp"
#include "csv_parser.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <map>
#include <stdexcept>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/covariance.hpp>

double StatisticalOperation::mean() const {
    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate mean for a column with no values (excluding header).");
    }

    // Check if the column contains numeric values
    bool isNumeric = true;
    for (size_t i = 1; i < column.size(); ++i) {
        if (!column[i].has_value() || !std::holds_alternative<double>(column[i].value())) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        // Numeric column, calculate mean
        boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
        for (size_t i = 1; i < column.size(); ++i) {
            if (column[i].has_value()) {
                acc(std::get<double>(column[i].value())); // Extract the double value from the variant
            }
        }
        return boost::accumulators::mean(acc);
        
    } else {
        throw std::invalid_argument("Column does not contain doubles.");
    }
}

double StatisticalOperation::variance() const { 

    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate variance for a column with no values (excluding header).");
    }
    
    // Check if the column contains numeric values
    bool isNumeric = true;
    for (size_t i = 1; i < column.size(); ++i) {
        if (!column[i].has_value() || !std::holds_alternative<double>(column[i].value())) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        // Numeric column, calculate mean
        boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;
        for (size_t i = 1; i < column.size(); ++i) {
            if (column[i].has_value()) {
                acc(std::get<double>(column[i].value())); // Extract the double value from the variant
            }
        }
        return boost::accumulators::variance(acc);
        
    } else {
        throw std::invalid_argument("Column does not contain doubles.");
    }

}

map<CSV_parser::ColumnField, int> StatisticalOperation::FrequencyCount() const {
    
    map<CSV::parser::ColumnField, int> dictionary; 

    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate variance for a column with no values (excluding header).");
    }

    // replenishing the map
    for (size_t i=1, i<column.size(); ++i) {
        if (column[i].has_value()){
            dictionary[column[i]]++;
        }
    }
    
    return dictionary;


}
