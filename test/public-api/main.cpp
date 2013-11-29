#include "../../libktomgirl.h"
#include <iostream>
//#include <libktomgirl/notemanager.hpp>

int main( int argc, char *argv[] )
{
  std::cout << " BEGIN " <<std::endl;
  gnote::NoteManager *man;
	man = new gnote::NoteManager();
	delete man;
  std::cout << " END " <<std::endl;
	return 0;
}
// Thu Nov 28 14:49:12 PST 2013
