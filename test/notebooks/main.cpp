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
	std::cout << "getting notebooks" << std::endl;
	Notebook::Ptr notebook = NotebookManager::instance().get_notebook(notebookName);
	std::cout << "getting notebooks name" << std::endl;
	std::cout << notebook->get_normalized_name();
	std::cout << "SUCCESS" << std::endl;

	return 0;
}
// Wed Oct 31 15:05:03 PDT 2012
