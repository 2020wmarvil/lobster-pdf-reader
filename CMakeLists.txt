cmake_minimum_required(VERSION 3.1)

project(Reader VERSION 1.0 DESCRIPTION "Automated reading of PDFs" LANGUAGES CXX)

SET(GCC_COVERAGE_COMPILE_FLAGS "-rdynamic")
SET(GCC_COVERAGE_LINK_FLAGS    "")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package(PythonLibs REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES main.cpp )
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES} ${PYTHON_LIBRARIES})
