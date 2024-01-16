cmake_minimum_required(VERSION 3.12)

project(AD2
	LANGUAGES CXX
	DESCRIPTION "Scientific Toolbox")

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Wno-deprecated-declarations)

## -- csv parser module--
### compile csvparser.so
add_library(libcsvparser SHARED src/csv_parser.hpp src/csv_parser.cpp)

### include header files for the library
target_include_directories(libcsvparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

## --statistical analysis module--
### find Boost

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message("Boost found")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found")
endif()

### compile csvparser.so
add_library(libstats SHARED src/statistics.hpp src/statistics.cpp)

### include header files for the library
target_include_directories(libstats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

### link against Boost and any other necessary libraries
target_link_libraries(libstats PRIVATE ${Boost_LIBRARIES})

# --BUILD EXECUTABLES--
add_executable(maincsv apps/main.cpp)

### link against library
target_link_libraries(maincsv PRIVATE libcsvparser libstats)

# --BUILDING PYTHON BINDING--
set(pybind11_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/pybind11/include")
find_package(pybind11 REQUIRED)

### csvparser binding 
pybind11_add_module(csvparser src/csv_parser.hpp src/csv_parser.cpp src/csv_bindings.cpp)

### statistics binding
pybind11_add_module(statistics src/statistics.hpp src/statistics.cpp src/stats_bindings.cpp)

### link against Boost and any other necessary libraries
target_link_libraries(statistics PRIVATE ${Boost_LIBRARIES})


