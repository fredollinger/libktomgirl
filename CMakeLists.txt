cmake_minimum_required(VERSION 2.8)
project(libtomgirl)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SIGC2 REQUIRED sigc++-2.0)
include_directories(${SIGC2_INCLUDE_DIRS})

find_package(LibXml2 REQUIRED)
include_directories(${LibXML_INCLUDE_DIRS})
include_directories("/usr/include/libxml2")

set (CMAKE_CXX_FLAGS "-fexceptions -lboost_filesystem-mt -lboost_date_time-mt -lpcrecpp")

set(ktomgirl_HEADERS
ktglib.hpp
xmlconvert.hpp
sharp.hpp
notemanager.hpp
files.hpp
gnote.hpp
tagmanager.hpp
notetag.hpp
exception.hpp
tag.hpp
debug.hpp
notebook.hpp
utils.hpp
preferences.hpp
datetime.hpp
note.hpp
map.hpp
triehit.hpp
xmlreader.hpp
macros.hpp
string.hpp
tree.hh
ktgtreeiter.hpp
xmlwriter.hpp
notebuffer.hpp
actionmanager.hpp
triecontroller.hpp
notebookmanager.hpp
notedata.hpp
xml.hpp
ktgtree.hpp
trie.hpp
search.hpp
)

set(ktomgirl_SRCS
actionmanager.cpp
datetime.cpp
debug.cpp
exception.cpp
files.cpp
gnote.cpp
notetag.cpp
ktglib.cpp
ktgtree.cpp
ktgtreeiter.cpp
note.cpp
notebook.cpp
notebookmanager.cpp
notebuffer.cpp
notedata.cpp
notemanager.cpp
preferences.cpp
sharp.cpp
search.cpp
string.cpp
tag.cpp
tagmanager.cpp
xml.cpp
xmlconvert.cpp
xmlreader.cpp
xmlwriter.cpp
utils.cpp
)

add_library(ktomgirl SHARED ${ktomgirl_SRCS})
# this might be a bug bug if we use project in dir such as include/{project}
# this will fail so I have to hard code it
install(FILES ${ktomgirl_HEADERS} DESTINATION include/libktomgirl)
# stupid bug means we can't glob subdirs so we need to so this one separately
install(FILES base/singleton.hpp DESTINATION include/libktomgirl/base)
INSTALL( TARGETS ktomgirl LIBRARY DESTINATION lib COMPONENT library)
