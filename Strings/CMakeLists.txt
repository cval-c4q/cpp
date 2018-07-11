CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
include(CheckCXXCompilerFlag)

project(Strings-test)

find_package(GTest REQUIRED)
find_package(Threads)

set(CMAKE_REQUIRED_LIBRARIES "-lasan")
check_cxx_compiler_flag("-fsanitize=address" HAVE_ASAN)
unset(CMAKE_REQUIRED_LIBRARIES)
check_cxx_compiler_flag("-fsanitize=leak" HAVE_LSAN)



option(ENABLE_ASAN "Enable building with ASAN" ON)
option(ENABLE_LSAN "Enable building with LSAN" OFF)

if(ENABLE_ASAN AND HAVE_ASAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
	set(CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES};-lasan")
elseif(ENABLE_LSAN AND HAVE_LSAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=leak")
endif()

if (ENABLE_ASAN AND HAVE_ASAN OR ENABLE_LSAN AND HAVE_LSAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${GTEST_INCLUDE_DIR})
add_executable(Strings-test Strings.cxx test.cxx)
target_link_libraries(Strings-test ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} Threads::Threads)
