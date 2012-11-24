//#include <QApplication>
//#include <QDebug>

#include <string>
#include <iostream>

//#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/note.hpp>
#include <libktomgirl/notebook.hpp>
#include <libktomgirl/notebookmanager.hpp>
#include <libktomgirl/notemanager.hpp>
#include <libktomgirl/tagmanager.hpp>
#include <libktomgirl/tag.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{
	gnote::NoteManager *m_gnmanager;
	m_gnmanager = new gnote::NoteManager();
	gnote::Note::Ptr note = m_gnmanager->find("Cycle Bullying: With Malice Towards None II");
	std::cout << "Title: " << note->get_title() << std::endl;
  	const char * NOTEBOOK_TAG_PREFIX = "notebook:";
	std::string name = "bob";
/*
	gnote::Tag::Ptr tag;
	gnote::Tag::Ptr t;

	std::cout << "get_or_create_system_tag()";
	tag = gnote::TagManager::obj().get_or_create_system_tag ( std::string(NOTEBOOK_TAG_PREFIX) + name);


	std::cout << "SUCCESS: get_or_create_system_tag()";
	t = gnote::TagManager::obj().get_tag ( std::string(NOTEBOOK_TAG_PREFIX) + name);
	std::cout << "calling add_tag(): \n" << t->name() << std::endl;
//	note->add_tag(tag);
	if (note->contains_tag(tag) )
		std::cout << "tag\n";
	else
		std::cout << "no tag\n";

//	note->save();
*/

        //Tag::Ptr t(new Tag(tag_name));
        gnote::Tag::Ptr t(new gnote::Tag(std::string(NOTEBOOK_TAG_PREFIX) + name));
	return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
