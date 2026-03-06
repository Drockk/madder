cmake_minimum_required(VERSION 3.28)

project(madder
    VERSION 0.1.0
    DESCRIPTION "High-performance async networking framework"
    LANGUAGES CXX
)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable C++ modules (not used in this project)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP OFF CACHE BOOL "Disable C++ modules")
set(CMAKE_CXX_SCAN_FOR_MODULES OFF CACHE BOOL "Disable C++ module scanning")

# =============================================================================
# Dependencies
# =============================================================================
include(cmake/dependencies.cmake)
