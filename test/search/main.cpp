#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notemanager.hpp>
#include <libktomgirl/search.hpp>

using namespace sharp;

int main( int argc, char *argv[] )
{
	gnote::NoteManager *m_gnmanager;
	m_gnmanager = new gnote::NoteManager();
	gnote::Search *m_searcher;
 // m_searcher = new gnote::Search(m_gnmanager);
	//gnote::Note::Ptr gnote = m_gnmanager->find("Cycle Bullying: With Malice Towards None II");
	//std::cout << "Title: " << gnote->get_title() << std::endl;

	return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
