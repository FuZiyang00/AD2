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
    try {
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
            // Numeric column, calculate variance
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
    
    // catching the error to allow for the execution to continue
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return 0;
    }
}


double StatisticalOperation::variance() const {
    try {
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
            // Numeric column, calculate variance
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
    
    } catch (const std::invalid_argument& e) {
        return 0;
    }
}


std::map<CSV_parser::ColumnField, int> StatisticalOperation::FrequencyCount() const {
    
    std::map<CSV_parser::ColumnField, int> dictionary; 

    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate variance for a column with no values (excluding header).");
    }
    for (size_t i = 1; i < column.size(); ++i) {
    if (column[i].has_value()) {
        dictionary[column[i].value()]++;  // Use .value() to access the optional's value
        }
    }   

    return dictionary;


}
