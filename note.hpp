/*
 * gnote
 *
 * Copyright (C) 2009 Hubert Figuiere
 *
 * Modified heavily 2012 by Fred Ollinger <follinge@gmail.com>
 * for KTomGirl
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
#ifndef __NOTE_HPP_
#define __NOTE_HPP_

#include <list>
#include <string>
#include <queue>

#include <memory>
#include <tr1/memory>

#include "base/singleton.hpp"

#include "xml.hpp"
#include "datetime.hpp"
#include "notedata.hpp"

class Tag;

namespace sharp {
  class XmlWriter;
}

namespace gnote {

class NoteManager;

class NoteData;
class NoteWindow;
class NoteTagTable;

class NoteDataBufferSynchronizer  
{
public:
// takes ownership
NoteDataBufferSynchronizer(NoteData * _data)
   : m_data(_data)
{
}

~NoteDataBufferSynchronizer();

const NoteData & getData() const
{
      return *m_data;
}

  NoteData & getData()
    {
      return *m_data;
    }

  const NoteData & synchronized_data() const
    {
      // synchronize_text();
      return *m_data;
    }
  NoteData & synchronized_data()
    {
      // synchronize_text();
      return *m_data;
    }

  const NoteData & data() const
    {
      return *m_data;
    }

  NoteData & data()
    {
      return *m_data;
    }
  const std::string & text();
  void set_text(const std::string & t);

private:
  void invalidate_text();
  bool is_text_invalid() const;
  //void synchronize_text(std::string&) const;
  // synchronize xml version of text w/ plain text version
  void synchronize_buffer();
  void buffer_changed();

  NoteData * m_data;
};


// BEGIN CLASS NOTE
class Note 
{
// BEGIN NOTE public:
public:
  void set_text_content(const std::string & text);
  std::string m_text_content;
  typedef std::tr1::shared_ptr<Note> Ptr;
  typedef std::tr1::weak_ptr<Note> WeakPtr;
  typedef std::list<Ptr> List;

  static void parse_tags(const xmlNodePtr tagnodes, std::list<std::string> & tags);

  typedef enum {
    NO_CHANGE,
    CONTENT_CHANGED,
    OTHER_DATA_CHANGED
  } ChangeType;

  ~Note();

  void changed(void);
  static std::string url_from_path(const std::string &);
  int get_hash_code() const;
  static Note::Ptr create_new_note(const std::string & title,
                                   const std::string & filename,
                                   NoteManager & manager);

  static Note::Ptr create_existing_note(NoteData *data,
                                        std::string filepath,
                                        NoteManager & manager);
  void delete_note();
  static Note::Ptr load(const std::string &, NoteManager &);
  void save();
  void queue_save(ChangeType c);

  bool is_open() {return m_is_open;};
  void set_is_open(bool b){ m_is_open = b; };
  const std::string & uri() const;
  const std::string id() const;
  const std::string & file_path() const
    {
      return m_filepath;
    }
  const std::string & get_title() const;
  std::string uid() const;
  void set_title(const std::string & new_tile);
  void rename_without_link_update(const std::string & newTitle);
  const std::string & xml_content()
    {
      return m_data.text();
    }
  void set_xml_content(const std::string & xml);
  std::string get_complete_note_xml();
  void load_foreign_note_xml(const std::string & foreignNoteXml, ChangeType changeType);
  std::string text_content();
  std::string text_content_plain();
  const NoteData & data() const;
  NoteData & data();

  NoteManager & manager()
    {
      return m_manager;
    }
  const NoteManager & manager() const
    {
      return m_manager;
    }

  bool is_special() const;
  bool is_new() const;

  bool is_pinned() const;
  void set_pinned(bool pinned) const;
  bool is_open_on_startup() const;
  void set_is_open_on_startup(bool);
  bool m_is_open;
// END NOTE public:

// BEGIN NOTE private:
private:
  void write(const std::string & _write_file, const NoteData & note);
  void on_buffer_changed();
  void on_save_timeout();
  void process_child_widget_queue();

  Note(NoteData * data, const std::string & filepath, NoteManager & manager);
  Note(Note*);

  struct ChildWidgetData{};

  NoteDataBufferSynchronizer m_data;
  std::string                m_filepath;
  /* FO: I added this. I can't wrap my mind around the whole convulted mess
   * that is NoteData and so on...
   */
  std::string                m_title;
  bool                       m_save_needed;
  bool                       m_is_deleting;
  NoteManager               &m_manager;
  std::queue<ChildWidgetData> m_child_widget_queue;
// END NOTE private:

}; // END class NOTE

// BEGIN class NOTEARCHIVER
class NoteArchiver
  : public base::Singleton<NoteArchiver>
{
public:
  static const char *CURRENT_VERSION;

  static NoteData *read(const std::string & read_file, const std::string & uri);
  static std::string write_string(const NoteData & data);
  static void write(const std::string & write_file, const NoteData & data);
  void write_file(const std::string & write_file, const NoteData & data);
  void write(sharp::XmlWriter & xml, const NoteData & note);

  std::string get_renamed_note_xml(const std::string &, const std::string &,
                                   const std::string &) const;
  std::string get_title_from_note_xml(const std::string & noteXml) const;

protected:
  NoteData *_read(const std::string & read_file, const std::string & uri);
};

namespace noteutils {
  // void show_deletion_dialog (const std::list<Note::Ptr> & notes, Gtk::Window * parent);
}

}
#endif
