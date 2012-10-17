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




#ifndef __TAG_MANAGER_HPP_
#define __TAG_MANAGER_HPP_

#include <map>
#include <memory>
#include <tr1/memory>
#include "base/singleton.hpp"
#include "tag.hpp"


namespace gnote {

class TagManager
  : public  base::Singleton<TagManager>
{
public:
  TagManager();

  typedef std::tr1::shared_ptr<Note> Ptr;
  // List is going to replace TreeModelColumn
  typedef std::list<Ptr> List;

  static const char * TEMPLATE_NOTE_SYSTEM_TAG;
  Tag::Ptr get_tag (const std::string & tag_name) const;
  Tag::Ptr get_or_create_tag(const std::string &);
  Tag::Ptr get_system_tag (const std::string & tag_name) const;
  Tag::Ptr get_or_create_system_tag(const std::string & name);
  void remove_tag (const Tag::Ptr & tag);
	#if 0
   Glib::RefPtr<Gtk::TreeModel> get_tags() const
    {
      return m_sorted_tags;
    }
#endif
  void all_tags(std::list<Tag::Ptr>  &) const;

private:

  class ColumnRecord
     : public List
  {
  public:
    ColumnRecord()
      {
        // add(m_tag);
      }
    // Gtk::TreeModelColumn<Tag::Ptr> m_tag;
	// FIXME: Need to implement this as a class which reimplements Gtk::TreeModelColumn stuff
	// which is used by the tag manager.
	// We probably need this to get started.
	Tag::Ptr m_tag;
	
  };
  ColumnRecord                     m_columns;
  // Glib::RefPtr<Gtk::ListStore>     m_tags;
  // Glib::RefPtr<Gtk::TreeModelSort> m_sorted_tags;
  // The key for this dictionary is Tag.Name.ToLower ().
  typedef std::map<std::string, Tag::Ptr> TagMap;
  TagMap                           m_tag_map;
  typedef std::map<std::string, Tag::Ptr> InternalMap;
  InternalMap                      m_internal_tags;
  // mutable Glib::Mutex              m_locker;
  
  // sigc::signal<void, Tag::Ptr, const Gtk::TreeIter &> m_signal_tag_added;
  // sigc::signal<void, const std::string &> m_signal_tag_removed;
};

}

#endif
