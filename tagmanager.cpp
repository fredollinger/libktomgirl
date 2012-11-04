/*
 * gnote
 *
 * Copyright (C) 2010 Debarshi Ray
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


//#include <string.h>
#include <iostream>

#include "tagmanager.hpp"
#include "debug.hpp"
#include "note.hpp"
#include "map.hpp"
#include "string.hpp"
#include "exception.hpp"

namespace gnote {

const char * TagManager::TEMPLATE_NOTE_SYSTEM_TAG = "template";

TagManager::TagManager()
    :  m_tags(new KTGlib::Tree())
    ,  m_sorted_tags(new KTGlib::Tree()) {
   // m_sorted_tags->set_sort_func (0, sigc::ptr_fun(&compare_tags_sort_func));
   // m_sorted_tags->set_sort_column_id (0, Gtk::SORT_ASCENDING);
} 

// BEGIN TagManager::get_tag ()
// <summary>
// Return an existing tag for the specified tag name.  If no Tag exists
// null will be returned.
// </summary>
Tag::Ptr TagManager::get_tag (const std::string & tag_name) const {
  std::cout << "TagManager::get_tag():FIXME: STUB" << std::endl;
    if (tag_name.empty())
      throw sharp::Exception("TagManager.GetTag () called with a null tag name.");

    std::string normalized_tag_name = sharp::string_to_lower(sharp::string_trim(tag_name));
    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetTag () called with an empty tag name.");

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");
    if ((splits.size() > 2) || Glib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)) {
//      Glib::Mutex::Lock lock(m_locker);
/*
      std::map<std::string, Tag::Ptr>::const_iterator iter = m_internal_tags.find(normalized_tag_name);
      if(iter != m_internal_tags.end()) {
        return iter->second;
      }
      return Tag::Ptr();
    }

    std::map<std::string, Gtk::TreeIter>::const_iterator iter = m_tag_map.find(normalized_tag_name);
    if (iter != m_tag_map.end()) {
      Gtk::TreeIter tree_iter = iter->second;
      return (*tree_iter)[m_columns.m_tag];
*/
	return tag;
    }

    return Tag::Ptr();
} // END TagManager::get_tag ()
  
// BEGIN TagManager::get_or_create_tag()
// <summary>
// Same as GetTag () but will create a new tag if one doesn't already exist.
// </summary>
Tag::Ptr TagManager::get_or_create_tag(const std::string & tag_name)
{
    if (tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with a null tag name.");

	std::string normalized_tag_name = sharp::string_to_lower(sharp::string_trim(tag_name));
	std::cout << "TagManager::get_or_create_tag()" << normalized_tag_name  <<std::endl;

    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with an empty tag name.");

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");

    // BEGIN IF VALID TAG
    if ((splits.size() > 2) || KTGlib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)){
      // TODO: MUTEX HERE?
      std::map<std::string, Tag::Ptr>::iterator iter;
      iter = m_internal_tags.find(normalized_tag_name);
      if(iter != m_internal_tags.end()) {
        return iter->second;
      }
      else {
        Tag::Ptr t(new Tag(tag_name));
        m_internal_tags [ t->normalized_name() ] = t;
        return t;

      }
    } // END IF VALID TAG

    // Gtk::TreeIter iter;
    bool tag_added = false;
    Tag::Ptr tag = get_tag (normalized_tag_name);

    // BEGIN if (!tag)
    if (!tag) {

    //  Glib::Mutex::Lock lock(m_locker);

      tag = get_tag (normalized_tag_name);
      if (!tag) {
        tag.reset(new Tag (sharp::string_trim(tag_name)));
    //    iter = m_tags->append ();
     //   (*iter)[m_columns.m_tag] = tag;
      //  m_tag_map [tag->normalized_name()] = iter;
        m_tag_map [tag->normalized_name()] = tag;

        tag_added = true;
      }
    } // END if (!tag)

// FIXME: BEGIN JUNK
        // Tag::Ptr t(new Tag(tag_name));
	return tag;
}
#if 0
    if (tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with a null tag name.");

    std::string normalized_tag_name = sharp::string_to_lower(sharp::string_trim(tag_name));
    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with an empty tag name.");

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");
    if ((splits.size() > 2) || Glib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)){
      Glib::Mutex::Lock lock(m_locker);
      std::map<std::string, Tag::Ptr>::iterator iter;
      iter = m_internal_tags.find(normalized_tag_name);
      if(iter != m_internal_tags.end()) {
        return iter->second;
      }
      else {
        Tag::Ptr t(new Tag(tag_name));
        m_internal_tags [ t->normalized_name() ] = t;
        return t;
      }
    }
    Gtk::TreeIter iter;
    bool tag_added = false;
    Tag::Ptr tag = get_tag (normalized_tag_name);
    if (!tag) {

      Glib::Mutex::Lock lock(m_locker);

      tag = get_tag (normalized_tag_name);
      if (!tag) {
        tag.reset(new Tag (sharp::string_trim(tag_name)));
        iter = m_tags->append ();
        (*iter)[m_columns.m_tag] = tag;
        m_tag_map [tag->normalized_name()] = iter;

        tag_added = true;
      }
    }

    if (tag_added) {
      m_signal_tag_added(tag, iter);
    }

    return tag;
  }
#endif
// END TagManager::get_or_create_tag()
    
  /// <summary>
  /// Same as GetTag(), but for a system tag.
  /// </summary>
  /// <param name="tag_name">
  /// A <see cref="System.String"/>.  This method will handle adding
  /// any needed "system:" or identifier needed.
  /// </param>
  /// <returns>
  /// A <see cref="Tag"/>
  /// </returns>
  Tag::Ptr TagManager::get_system_tag (const std::string & tag_name) const
  {
    return get_tag(Tag::SYSTEM_TAG_PREFIX + tag_name);
  }
    
  /// <summary>
  /// Same as <see cref="Tomboy.TagManager.GetSystemTag"/> except that
  /// a new tag will be created if the specified one doesn't exist.
  /// </summary>
  /// <param name="tag_name">
  /// A <see cref="System.String"/>
  /// </param>
  /// <returns>
  /// A <see cref="Tag"/>
  /// </returns>
  Tag::Ptr TagManager::get_or_create_system_tag (const std::string & tag_name)
  {
    return get_or_create_tag(Tag::SYSTEM_TAG_PREFIX + tag_name);
  }
    

    // <summary>
    // This will remove the tag from every note that is currently tagged
    // and from the main list of tags.
    // </summary>
  void TagManager::remove_tag (const Tag::Ptr & tag)
  {
#if 0
    if (!tag)
      throw sharp::Exception ("TagManager.RemoveTag () called with a null tag");

    if(tag->is_property() || tag->is_system()){

      Glib::Mutex::Lock lock(m_locker);

      m_internal_tags.erase(tag->normalized_name());
    }
    bool tag_removed = false;
    std::map<std::string, Gtk::TreeIter>::iterator map_iter;
    map_iter = m_tag_map.find(tag->normalized_name());
    if (map_iter != m_tag_map.end()) {

      Glib::Mutex::Lock lock(m_locker);

      map_iter = m_tag_map.find(tag->normalized_name());
      if (map_iter != m_tag_map.end()) {
        Gtk::TreeIter iter = map_iter->second;
        if (!m_tags->erase(iter)) {
          DBG_OUT("TagManager: Removed tag: %s", tag->normalized_name().c_str());
        } 
        else { 
          // FIXME: For some really weird reason, this block actually gets called sometimes!
          DBG_OUT("TagManager: Call to remove tag from ListStore failed: %s", tag->normalized_name().c_str());
        }

        m_tag_map.erase(map_iter);
        DBG_OUT("Removed TreeIter from tag_map: %s", tag->normalized_name().c_str());
        tag_removed = true;

        std::list<Note*> notes;
        tag->get_notes(notes);
        for(std::list<Note*>::const_iterator note_iter = notes.begin();
            note_iter != notes.end(); ++note_iter) {
          (*note_iter)->remove_tag(tag);
        }
      }
    }

    if (tag_removed) {
      m_signal_tag_removed(tag->normalized_name());
    }
#endif
  }
  
void TagManager::all_tags(std::list<Tag::Ptr> & tags) const {
    std::cout << "TagManager::all_tags" << std::endl;
    // Add in the system tags first
    sharp::map_get_values(m_internal_tags, tags);

	// FIXME: Delete next line:
    TagMap::const_iterator iter = m_tag_map.begin();

    std::cout << "TagManager::all_tags2" << std::endl;

	std::cout << "mymap.size() is " << (int) m_tag_map.size() << std::endl;
	if (m_tag_map.empty()) return;
    std::cout << "TagManager::all_tags3" << std::endl;
    // Now all the other tags
    for(TagMap::const_iterator iter = m_tag_map.begin();
        iter != m_tag_map.end(); ++iter) {
		std::cout << "TagManager::all_tags4" << std::endl;
      	Tag::Ptr tag;
      	// FIXME: NEED TO TEST
      	//iter->second->get_value(0, tag);      
      	tag = iter->second;
     	tags.push_back(tag);
    }
} // END TagManager::all_tags()

#if 0 
  // <summary>
  // Same as GetTag () but will create a new tag if one doesn't already exist.
  // </summary>
  Tag::Ptr TagManager::get_or_create_tag(const std::string & tag_name)
  {
    if (tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with a null tag name.");

    std::string normalized_tag_name = sharp::string_to_lower(sharp::string_trim(tag_name));
    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with an empty tag name.");

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");

    if ((splits.size() > 2) || Glib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)){
      Glib::Mutex::Lock lock(m_locker);

      std::map<std::string, Tag::Ptr>::iterator iter;
      iter = m_internal_tags.find(normalized_tag_name);
      if(iter != m_internal_tags.end()) {
        return iter->second;
      }
      else {
        Tag::Ptr t(new Tag(tag_name));
        m_internal_tags [ t->normalized_name() ] = t;
        return t;

      }

    }

    Gtk::TreeIter iter;
    bool tag_added = false;
    Tag::Ptr tag = get_tag (normalized_tag_name);

    if (!tag) {

      Glib::Mutex::Lock lock(m_locker);

      tag = get_tag (normalized_tag_name);
      if (!tag) {
        tag.reset(new Tag (sharp::string_trim(tag_name)));
        iter = m_tags->append ();
        (*iter)[m_columns.m_tag] = tag;
        m_tag_map [tag->normalized_name()] = iter;

        tag_added = true;
      }
    }

    if (tag_added) {
      m_signal_tag_added(tag, iter);
    }

    return tag;
  }
#endif
   
} // namespace gnote 
