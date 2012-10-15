#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notebook.hpp>
//#include <libktomgirl/notemanager.hpp>
#include <libktomgirl/notebookmanager.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{
	std::string notebookName = "joe";
    Notebook::Ptr notebook = NotebookManager::instance().get_or_create_notebook (notebookName);

	return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
