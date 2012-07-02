/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <string.h>
#include <exception>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "../libtomgirl/datetime.hpp"
#include "../libtomgirl/debug.hpp"
#include "../libtomgirl/files.hpp"
#include "ktglib.hpp"
#include "gnote.hpp"
#include "note.hpp"
#include "notemanager.hpp"
#include "preferences.hpp"
#include "../libtomgirl/sharp.hpp"
#include "../libtomgirl/string.hpp"

namespace gnote {
NoteManager::NoteManager(const std::string & directory, const std::string & backup) 
{
    _common_init(directory, backup);
}

NoteManager::NoteManager() 
{
	std::string directory = Gnote::data_dir();
	std::string backup = "";
	_common_init(directory, backup);
}

void NoteManager::_common_init(const std::string & directory, const std::string & backup_directory)
  {
    m_addin_mgr = NULL;

    Preferences & prefs(Preferences::obj());

    // m_note_template_title = tr("New Note Template");

    DBG_OUT("NoteManager created with note path \"%s\".", directory.c_str());

    m_notes_dir = directory;
    m_backup_dir = backup_directory;

    create_notes_dir ();

    // FIXME: We need to re-implement first run jazz...eventually...first:
    load_notes ();

#if 0
    bool is_first_run = first_run ();

    const std::string old_note_dir = Gnote::old_note_dir();
    const bool migration_needed
                 = is_first_run
                   && sharp::directory_exists(old_note_dir);

    if (migration_needed) {
      migrate_notes(old_note_dir);
      is_first_run = false;
    }

    m_addin_mgr = create_addin_manager ();

    if (is_first_run) {
      std::list<ImportAddin*> l;
      m_addin_mgr->get_import_addins(l);
      bool has_imported = false;

      if(l.empty()) {
        DBG_OUT("no import plugins");
      }

      for(std::list<ImportAddin*>::iterator iter = l.begin();
          iter != l.end(); ++iter) {

        DBG_OUT("importing");
        (*iter)->initialize();
        if((*iter)->want_to_run(*this)) {
          has_imported |= (*iter)->first_run(*this);
        }
      }
      // we MUST call this after import
      post_load();

      // First run. Create "Start Here" notes.
      create_start_notes ();
    } 
    else {
      load_notes ();
    }
#endif
  }

  NoteManager::~NoteManager()
  {
    // delete m_addin_mgr;
  }

// BEGIN NoteManager::create_new_note()
// Create a new note with the specified title, and a simple
// "Describe..." body or the body from the "New Note Template"
// note if it exists.  If the "New Note Template" body is found
// the text will not automatically be highlighted.
// Note::Ptr NoteManager::create_new_note (std::string title, const std::string & guid)
Note::Ptr NoteManager::create_new_note (const std::string &title, const std::string &uid)
{
	std::string filename = m_notes_dir +"/" + uid + ".note";
    	Note::Ptr new_note = Note::create_new_note (title, filename, *this);
    	add_note(new_note);
   	return new_note; 
}
// END NoteManager::create_new_note()

// BEGIN LOAD_NOTE
  Note::Ptr NoteManager::load_note(const std::string & file_path)
  {
    std::string dest_file = file_path;

    Note::Ptr note;

    note = Note::load(dest_file, *this);
    add_note(note);

    return note;
  }
// END LOAD_NOTE

  void NoteManager::add_note(const Note::Ptr & note)
  {
    if (note) {
      m_notes.push_back(note);
    }
  }

// BEGIN LOAD_NOTES
void NoteManager::load_notes()
{
    std::list<std::string> files;
    sharp::directory_get_files_with_ext(m_notes_dir, ".note", files);


    for(std::list<std::string>::const_iterator iter = files.begin();
        iter != files.end(); ++iter) {
      const std::string & file_path(*iter);
      try {
        Note::Ptr note = Note::load(file_path, *this);
        add_note(note);
      } 
      catch (const std::exception & e) {
        //ERR_OUT("Error parsing note XML, skipping \"%s\": %s",
                //file_path.c_str(), e.what());
      }
      //std::cout << "adding note: " << file_path;
    }
    // post_load();
    // Make sure that a Start Note Uri is set in the preferences, and
    // make sure that the Uri is valid to prevent bug #508982. This
    // has to be done here for long-time Tomboy users who won't go
    // through the create_start_notes () process.
    #if 0
    if (start_note_uri().empty() ||
        !find_by_uri(start_note_uri())) {
      // Attempt to find an existing Start Here note
      Note::Ptr start_note = find (_("Start Here"));
      if (start_note) {
        Preferences::obj().set<std::string>(Preferences::START_NOTE_URI, start_note->uri());
      }
    }
    #endif
}
// END LOAD_NOTES

  Note::Ptr NoteManager::find_by_uri(const std::string & uri) const
  {
    for(Note::List::const_iterator iter = m_notes.begin();
        iter != m_notes.end(); ++iter) {
      const Note::Ptr & note(*iter);
      if (note->uri() == uri) {
        return note;
      }
    }
    return Note::Ptr();
  }


std::string NoteManager::make_new_file_name(const std::string & guid) const
{
	return m_notes_dir + "/" + guid + ".note";
}

bool NoteManager::first_run() const
{

    return boost::filesystem::exists(m_notes_dir);
}

// Create the notes directory if it doesn't exist yet.
void NoteManager::create_notes_dir() const
{

 	create_directory(m_notes_dir);
}

// For overriding in test methods.
bool NoteManager::create_directory(const std::string & path) const
{
    return boost::filesystem::create_directory(path);
}

  Note::Ptr NoteManager::find(const std::string & linked_title) const
  {
    for(Note::List::const_iterator iter = m_notes.begin();
        iter != m_notes.end(); ++iter) {
      const Note::Ptr & note(*iter);
      if (sharp::string_to_lower(note->get_title()) == sharp::string_to_lower(linked_title))
        return note;
    }
    return Note::Ptr();
  }

// BEGIN NoteManager::delete_note()
void NoteManager::delete_note(const Note::Ptr & note)
{
    if (boost::filesystem::exists(note->file_path())) {
      if (!m_backup_dir.empty()) {
        if (!boost::filesystem::exists(m_backup_dir)) {
          boost::filesystem::create_directory(m_backup_dir);
        }
        std::string backup_path 
          = KTGlib::build_filename(m_backup_dir, sharp::file_filename(note->file_path()));
          
        if (boost::filesystem::exists(backup_path))
          boost::filesystem::remove(backup_path);

        boost::filesystem::rename(note->file_path(), backup_path);
      } 
      else {
        boost::filesystem::remove(note->file_path());
      }
    }

    //m_notes.removeAll(note);
    m_notes.clear();
    note->delete_note();
}
// END NoteManager::delete_note()
} // namespace gnote
// Sun May 27 14:07:53 PDT 2012
