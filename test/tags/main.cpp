#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notebook.hpp>
#include <libktomgirl/notebookmanager.hpp>
#include <libktomgirl/tagmanager.hpp>
#include <libktomgirl/tag.hpp>
#include <libktomgirl/tagmanager.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{

  	const char * NOTEBOOK_TAG_PREFIX = "notebook:";

     	gnote::TagManager *man = new gnote::TagManager(); 
	gnote::Tag::Ptr tag; 
        //Notebook::Ptr notebook;

	std::string name = "bob";

	Notebook::Ptr notebook = NotebookManager::instance().get_or_create_notebook (name);

        // notebook = Notebook::Ptr(new Notebook (name));

//	tag = gnote::TagManager::obj().get_or_create_system_tag ( std::string(NOTEBOOK_TAG_PREFIX) + name);

	std::cout << notebook->get_normalized_name();


	return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
