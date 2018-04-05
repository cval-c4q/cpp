
#include(ExternalProject)
#ExternalProject_Add(googletest
#	GIT_REPOSITORY	https://github.com/google/googletest.git
#	GIT_TAG	master
#	SOURCE_DIR	"${CMAKE_BINARY_DIR}/googletest-src"
#	BINARY_DIR	"${CMAKE_BINARY_DIR}/googletest-build"
#	CONFIGURE_COMMAND	""
#	BUILD_COMMAND		""
#	INSTALL_COMMAND		""
#	TEST_COMMAND		""
#)

include_directories(${PROJECT_SOURCE_DIR})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
set (EXTRA_LIBS ${EXTRA_LIBS} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} Threads::Threads)

##
##  Targets
add_executable(person-methods person-methods.cpp)
target_link_libraries(person-methods person ${EXTRA_LIBS})
