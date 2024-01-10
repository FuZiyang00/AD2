#include "statistics.hpp"
#include "csv_parser.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <map>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/covariance.hpp>

double StatisticalOperation::mean() const {
    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate mean for a column with no or one value (excluding header).");
    }

    // Check if the column contains numeric values
    bool isNumeric = std::all_of(column.begin() + 1, column.end(), [](const auto& val) {
        return val.has_value() && std::holds_alternative<double>(val.value());
    });

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
        throw std::out_of_range("Column does not contain doubles.");
    }
}