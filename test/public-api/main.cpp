#include "../../libktomgirl.h"
#include <iostream>

int main( int argc, char *argv[] )
{
  std::cout << " BEGIN " <<std::endl;
  gnote::NoteManager *man;
	man = new gnote::NoteManager();
	delete man;

	//gnote::notebooks::Notebook *nb = new gnote::notebooks::Notebook();

	//gnote::notebooks::NotebookManager::instance().get_or_create_notebook("bob");

  gnote::notebooks::NotebookManager::instance().get_notebook("bob");

  std::cout << " END " <<std::endl;
	return 0;
}
// Thu Nov 28 14:49:12 PST 2013
