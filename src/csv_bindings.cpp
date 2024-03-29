#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "csv_parser.hpp"

namespace py = pybind11;

PYBIND11_MODULE(csvparser_module, m) {
    m.doc() = "Python bind of CSV_parser class";

    py::class_<CSV_parser>(m, "CSV_parser")
        .def(py::init<const std::string&>())
        .def("parseCSV", &CSV_parser::parseCSV)
        .def("displayTable", &CSV_parser::displayTable)
        .def("getCSVData", &CSV_parser::getCSVData);
}

