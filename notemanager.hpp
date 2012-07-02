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
#ifndef _NOTEMANAGER_HPP__
#define _NOTEMANAGER_HPP__

#include <string>
#include <list>
#include <memory>

#include <boost/shared_ptr.hpp>

#include "note.hpp"

namespace gnote {

  class AddinManager;
  class TrieController;

class NoteManager 
{
// BEGIN PUBLIC
public:
    typedef boost::shared_ptr<NoteManager> Ptr;
    
    bool first_run() const;
    NoteManager(const std::string & directory, const std::string & backup);
    NoteManager();
    ~NoteManager();

    void create_notes_dir(void) const;

    Note::Ptr create_new_note (const std::string &, const std::string &);
    Note::Ptr load_note(const std::string & file_path);

    const Note::List & get_notes() const
      { 
        return m_notes;
      }

    // the trie for the note names
    size_t trie_max_length();

    AddinManager & get_addin_manager()
      {
        return *m_addin_mgr;
      }
    const std::string & get_notes_dir() const
      {
        return m_notes_dir;
      }
    const std::string & start_note_uri() const
      { 
        return m_start_note_uri; 
      }
    Note::Ptr find(const std::string &) const;
    Note::Ptr find_by_uri(const std::string &) const;
    void delete_note(const Note::Ptr & note);

    Note::Ptr create();
    Note::Ptr create(const std::string & title);
    Note::Ptr create(const std::string & title, const std::string & xml_content);
    // Import a note read from file_path
    // Will ensure the sanity including the unique title.
    Note::Ptr import_note(const std::string & file_path);
    Note::Ptr create_with_guid(const std::string & title, std::string & guid);
    Note::Ptr get_or_create_template_note();
    static std::string get_note_template_content(const std::string & title);
    static std::string split_title_from_content (std::string title, std::string & body);

    void signal_note_deleted(void);
    void signal_note_added(void);
    void signal_note_renamed(void);
    void signal_note_saved(void);
    void m_signal_start_note_created(void);
// END PUBLIC

/*
signals:

	void signal_note_deleted(void);
	void signal_note_added(void);
	void signal_note_renamed(void);
	void signal_note_saved(void);
    	void m_signal_start_note_created(void);

*/


private:
    bool create_directory(const std::string & directory) const;
    void on_note_rename(const Note::Ptr & note, const std::string & old_title);
    void create_start_notes();
    void on_note_save(const Note::Ptr & note);
    void load_notes();
    void post_load();
    bool on_exiting_event();
    std::string make_new_file_name() const;
    std::string make_new_file_name(const std::string & guid) const;
    /** add the note to the manager and setup signals */
    void add_note(const Note::Ptr &);
    void _common_init(const std::string & directory, const std::string & backup);

    std::string m_notes_dir;
    std::string m_backup_dir;
    Note::List m_notes;
    AddinManager   *m_addin_mgr;
    std::string m_note_template_title;
    std::string m_start_note_uri;

#if 0
    //Note::Ptr create_new_note (std::string title, const std::string & guid);
    //Note::Ptr create_new_note (const std::string & title, const std::string & xml_content, 
    //                         const std::string & guid);
    bool first_run() const;
    void create_notes_dir() const;
#endif   
  };


}

#endif

