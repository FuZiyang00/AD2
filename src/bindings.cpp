#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "csv_parser.hpp"
#include "statistics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(csv_parser, m) {
    py::class_<CSV_parser>(m, "CSV_parser")
        .def(py::init<const std::string&>())
        .def("parseCSV", &CSV_parser::parseCSV)
        .def("displayTable", &CSV_parser::displayTable)
        .def("getCSVData", &CSV_parser::getCSVData);
}


PYBIND11_MODULE(statistics, m) {
    py::class_<StatisticalOperation>(m, "StatisticalOperation")
        .def(py::init([](const std::vector<std::optional<ColumnField>>& column, const std::vector<Column>& data) {
            return new StatisticalOperation(column, data);
        })) // Lambda constructor to tell Python what types column and data are

        // don't need to worry adout new because Python has its garbage collector

        .def("mean", &StatisticalOperation::mean)
        .def("variance", &StatisticalOperation::variance)
        .def("FrequencyCount", &StatisticalOperation::FrequencyCount);
}
