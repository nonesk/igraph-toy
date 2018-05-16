cmake_minimum_required(VERSION 3.0.0)
project(igraph VERSION 0.1.0)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

file(
    GLOB
    source_files
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(main ${source_files} )

find_package(IGRAPH REQUIRED)

message(STATUS "IGRAPH found")

include_directories(${IGRAPH_INCLUDE_DIRS})
link_directories(${IGRAPH_LIBRARIES})
message(STATUS "Include path : ${IGRAPH_INCLUDE_DIRS}")
message(STATUS "Lib path : ${IGRAPH_LIBRARIES}")
target_link_libraries(main ${IGRAPH_LIBRARIES})