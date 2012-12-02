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
	std::string notebookName = "bill";
	std::cout << "getting notebooks" << std::endl;
	Notebook::Ptr notebook = NotebookManager::instance().get_or_create_notebook(notebookName);
	notebookName = "joe";
	Notebook::Ptr notebook2 = NotebookManager::instance().get_or_create_notebook(notebookName);
  /*
	std::cout << "getting notebooks name..." << std::endl;
	std::cout << notebook->get_normalized_name();
	std::cout << notebook2->get_normalized_name();
  */

	KTGlib::StringList fifth = NotebookManager::instance().get_notebook_list();
  std::cout << "notebook list size: "<< fifth.size() << std::endl;
	for (KTGlib::StringList::iterator it = fifth.begin(); it != fifth.end(); it++){
   		std::cout << "notebook: "<< *it << " ";
  		std::cout << endl;
	 }

	return 0;
}
// Sat Dec  1 19:51:48 PST 2012
