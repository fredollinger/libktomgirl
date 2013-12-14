cmake_minimum_required (VERSION 2.6) 
project (search) 

find_package(LibXml2 REQUIRED)
include_directories(${LibXML_INCLUDE_DIRS})
include_directories("/usr/include/libxml2")

set (CMAKE_CXX_FLAGS "-lktomgirl")

add_executable (search main.cpp) 
