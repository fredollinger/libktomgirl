cmake_minimum_required(VERSION 2.8)
project(libtomgirl)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGC2 REQUIRED sigc++-2.0)
include_directories(${SIGC2_INCLUDE_DIRS})

find_package(LibXml2 REQUIRED)
include_directories(${LibXML_INCLUDE_DIRS})
include_directories("/usr/include/libxml2")

set (CMAKE_CXX_FLAGS "-fexceptions -lboost_filesystem-mt -lboost_date_time-mt -lpcrecpp -lxml2 -lktomgirl")

set(ktomgirl_SRCS
main.cpp
)

add_executable (api-test ${ktomgirl_SRCS}) 
