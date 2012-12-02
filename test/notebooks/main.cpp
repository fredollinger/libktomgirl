#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notebookmanager.hpp>
#include <libktomgirl/notemanager.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{
	gnote::NoteManager *m_gnmanager;
	m_gnmanager = new gnote::NoteManager();
  std::string title = "Notemanager Test Note";
  gnote::Note::Ptr gnote = m_gnmanager->create_new_note (title, "");
	//gnote = m_gnmanager->find(title);

  gnote::notebooks::NotebookManager::instance().get_or_create_notebook("one");
  gnote::notebooks::NotebookManager::instance().get_or_create_notebook("two");

  gnote::notebooks::NotebookManager::instance().move_note_to_notebook(gnote, "one");
  gnote::notebooks::NotebookManager::instance().move_note_to_notebook(gnote, "two");
  gnote->save();

	Notebook::Ptr notebook = NotebookManager::instance().get_notebook_from_note(gnote);
	std::cout << "Title: " << gnote->get_title() << std::endl;

  if (notebook)
	  std::cout << "Notebook: " << notebook->get_name() << std::endl;
  else
	  std::cout << "This note has no notebook." << std::endl;


	return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
