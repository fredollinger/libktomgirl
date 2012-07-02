cmake_minimum_required(VERSION 2.8)
project(libtomgirl)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGC2 REQUIRED sigc++-2.0)
include_directories(${SIGC2_INCLUDE_DIRS})

find_package(LibXml2 REQUIRED)
include_directories(${LibXML_INCLUDE_DIRS})
include_directories("/usr/include/libxml2")

set (CMAKE_CXX_FLAGS "-fexceptions -lboost_filesystem-mt -lboost_date_time-mt -lpcrecpp")

set(ktomgirl_SRCS
actionmanager.cpp
datetime.cpp
debug.cpp
files.cpp
gnote.cpp
ktglib.cpp
note.cpp
notebuffer.cpp
notedata.cpp
notemanager.cpp
preferences.cpp
sharp.cpp
string.cpp
tag.cpp
xml.cpp
xmlconvert.cpp
xmlreader.cpp
xmlwriter.cpp
)

add_library(ktomgirl SHARED ${ktomgirl_SRCS})
#target_link_libraries(${LibXML_LIBRARIES}  ${SIGC2_LIBRARIES} )

#install(TARGETS libtomgirl  DESTINATION ${LIB_INSTALL_DIR})
#install(FILES  DESTINATION ${_INSTALL_DIR}/ktomgirl)
#install(FILES DESTINATION ${BIN_INSTALL_DIR})
# Sat Jun  9 16:38:25 PDT 2012
