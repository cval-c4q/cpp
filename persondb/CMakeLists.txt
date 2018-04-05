cmake_minimum_required(VERSION 3.1)
project(persondb VERSION 0.0.1 LANGUAGES CXX)

option (BUILD_TESTS
	"Build unit tests" ON)

if (BUILD_TESTS)
	add_subdirectory(test)
endif (BUILD_TESTS)

#include_directories(${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
add_library(person person.cpp)
target_link_libraries(person ${EXTRA_LIBS})


