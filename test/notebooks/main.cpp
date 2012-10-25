#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notebook.hpp>
#include <libktomgirl/notebookmanager.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{
	std::string notebookName = "bob";
	Notebook::Ptr notebook = NotebookManager::instance().get_notebook(notebookName);
	std::cout << notebook->get_normalized_name();

	return 0;
}
// Wed Oct 24 18:23:03 PDT 2012
