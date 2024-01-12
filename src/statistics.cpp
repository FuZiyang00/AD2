#include "statistics.hpp"
#include "csv_parser.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <map>
#include <stdexcept>
#include<algorithm>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/covariance.hpp>

double StatisticalOperation::mean() const {
    if (column.size() <= 1) {
        throw std::runtime_error(
            "Cannot calculate mean for a column with no or one value (excluding header).");
    }

    /// Check if the column contains only numeric values (doubles)
    auto isNumeric = [](const auto& val) {
        return val.has_value() && std::holds_alternative<double>(val.value());
    };

    if (std::all_of(column.begin(), column.end(), isNumeric)) {
        // Numeric column, calculate mean using Boost Accumulators library
        boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
        for (const auto& value : column) {
            if (value.has_value()) {
                acc(std::get<double>(value.value())); // Extract the double value from the variant
            }
        }
        return boost::accumulators::mean(acc);
    } else {
        // Non-numeric column, throw an exception
        throw std::invalid_argument("Column does not contain doubles.");
    }
}