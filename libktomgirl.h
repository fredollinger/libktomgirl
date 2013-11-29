/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 *
 * 2012 Modified by Fred Ollinger <follinge@gmail.com> for KTomGirl
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
#ifndef __LIBKTOMGIRL_H__
#define __LIBKTOMGIRL_H__

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <queue>
#include <tr1/memory>

namespace KTGlib {
    class Tree;
    typedef std::list<std::string> StringList;
} // namespace KTGlib

namespace base {
  template <class _Type>
  class Singleton 
  {
  public:
    static _Type & obj()
      {
        // TODO make this thread safe;
        static _Type * instance = new _Type();
        return *instance;
      }

  };
} // namespace base {

namespace gnote {
  class AddinManager;
  class TrieController;

class Note{
public:
  typedef std::tr1::shared_ptr<Note> Ptr;
  typedef std::tr1::weak_ptr<Note> WeakPtr;
  typedef std::list<Ptr> List;
};

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

    const std::string & get_notes_dir() const
      {
        return m_notes_dir;
      }
    const std::string & start_note_uri() const
      { 
        return m_start_note_uri; 
      }
    Note::Ptr create(const std::string & title);
    Note::Ptr create_with_guid(const std::string & title, std::string & guid);

    void delete_note(const Note::Ptr & note);

    Note::Ptr find(const std::string &) const;
    Note::Ptr find_by_uri(const std::string &) const;

    // Import a note read from file_path
    // Will ensure the sanity including the unique title.
    Note::Ptr import_note(const std::string & file_path);

    Note::Ptr get_or_create_template_note();
    static std::string get_note_template_content(const std::string & title);
    static std::string split_title_from_content (std::string title, std::string & body);

    void signal_note_deleted(void);
    void signal_note_added(void);
    void signal_note_renamed(void);
    void signal_note_saved(void);
    void m_signal_start_note_created(void);
// END PUBLIC

private:
    std::string m_notes_dir;
    std::string m_start_note_uri;
    Note::List m_notes;
    std::string m_backup_dir;
    std::string m_note_template_title;
  }; // class NoteManager 

class Tag{
public:
    typedef std::tr1::shared_ptr<Tag> Ptr;
    static const char * SYSTEM_TAG_PREFIX;

    Tag(const std::string & name);
    ~Tag();
private:
    class NoteMap;
    std::string m_name;
    std::string m_normalized_name;
    bool        m_issystem;
    bool        m_isproperty;
    // <summary>
    // Used to track which notes are currently tagged by this tag.  The
    // dictionary key is the Note.Uri.
    // </summary>
    NoteMap *   m_notes;
}; // class Tag

class TagManager
  : public  base::Singleton<TagManager>
{
public:
  TagManager();
  typedef std::tr1::shared_ptr<Note> Ptr;
  void all_tags(std::list<Tag::Ptr>  &) const;
  typedef std::list<Ptr> List;
private:
	Tag::Ptr m_tag;
  std::auto_ptr<KTGlib::Tree>     m_tags;
  std::auto_ptr<KTGlib::Tree>     m_sorted_tags;
  typedef std::map<std::string, Tag::Ptr> TagMap;
  TagMap                           m_tag_map;
  TagMap m_internal_tags;
}; // class TagManager


namespace notebooks {
class Notebook{
public:
  typedef std::tr1::shared_ptr<Notebook> Ptr;
}; // class Notebook

class NotebookManager{
public:
  static NotebookManager & instance()
    {
      static NotebookManager *s_instance = new NotebookManager();
      return *s_instance;
  }
  Notebook::Ptr get_or_create_notebook(const std::string &);
  Notebook::Ptr get_notebook_from_note(const Note::Ptr &);
  Notebook::Ptr get_notebook(const std::string & notebookName) const;
private:
  std::map<std::string, Notebook::Ptr> m_notebookMap;
  KTGlib::StringList m_notebookList;
  bool                                 m_adding_notebook;
}; // class NoteookManager
} // namespace notebooks 
} // namespace gnote 
#endif // __LIBKTOMGIRL_H__
// Thu Nov 28 15:58:07 PST 2013
