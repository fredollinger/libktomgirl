#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notemanager.hpp>

using namespace sharp;

int main( int argc, char *argv[] ){
	gnote::NoteManager *m_gnmanager;
	m_gnmanager = new gnote::NoteManager();
  gnote::Note::Ptr gnote = m_gnmanager->find_by_uri("667c6f9d-ad6b-4e2c-bc80-c919b7396763");
	if ( NULL != gnote)
				std::cout << "Title: " << gnote->get_title() << std::endl;
  else
        std::cout << "failed to load note" << std::endl;

	return 0;
}
