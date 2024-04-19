cmake_minimum_required(VERSION 3.10)
project(Amino)

file(GLOB_RECURSE SOURCES "Amino/*.cpp")
file(GLOB_RECURSE HEADERS "Amino/*.h" "Amino/*.hpp")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found.")
endif()
if(NOT HEADERS)
    message(FATAL_ERROR "No header files found.")
endif()

add_library(Amino STATIC ${SOURCES} ${HEADERS})
set_target_properties(Amino PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")

target_include_directories(Amino PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
