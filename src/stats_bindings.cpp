#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "csv_parser.hpp"
#include "statistics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(statistics, m) {
    m.doc() = "Python bind of statistics class";
    py::class_<StatisticalOperation>(m, "StatisticalOperation")
        .def(py::init([](const std::vector<std::optional<CSV_parser::ColumnField>>& column, const CSV_parser::Table& data) {
            return new StatisticalOperation(column, data);
        }))
        .def("mean", &StatisticalOperation::mean)
        .def("variance", &StatisticalOperation::variance)
        .def("FrequencyCount", &StatisticalOperation::FrequencyCount);
}

// Export function for Python to recognize the module
PyMODINIT_FUNC PyInit_statistics() {
    return PyModule_Create(&statistics);
}


