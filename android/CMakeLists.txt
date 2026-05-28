project(NitroBarcode)
cmake_minimum_required(VERSION 3.9.0)

set(PACKAGE_NAME NitroBarcode)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE shared_files RELATIVE ${CMAKE_SOURCE_DIR} "../cpp/**.cpp")

add_library(${PACKAGE_NAME} SHARED ${shared_files})

include(${CMAKE_SOURCE_DIR}/../nitrogen/generated/android/NitroBarcode+autolinking.cmake)

include_directories("../cpp")

find_library(LOG_LIB log)

target_link_libraries(${PACKAGE_NAME} ${LOG_LIB} android)
