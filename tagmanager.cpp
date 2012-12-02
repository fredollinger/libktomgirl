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
    //,  m_internal_tags(new KTGlib::Tree()) {
   // m_sorted_tags->set_sort_func (0, sigc::ptr_fun(&compare_tags_sort_func));
   // m_sorted_tags->set_sort_column_id (0, Gtk::SORT_ASCENDING);
} 

// BEGIN TagManager::get_tag ()
// <summary>
// Return an existing tag for the specified tag name.  If no Tag exists
// null will be returned.
// </summary>
Tag::Ptr TagManager::get_tag (const std::string & tag_name) const {
    if (tag_name.empty())
      throw sharp::Exception("TagManager.GetTag () called with a null tag name.");

    std::string normalized_tag_name = sharp::string_to_lower(sharp::string_trim(tag_name));
    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetTag () called with an empty tag name.");

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");
    if ((splits.size() > 2) || KTGlib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)) 
    {
  	    KTGlib::Tree m_internal_tags;
      	KTGlib::TreeIter iter = m_internal_tags.find(normalized_tag_name);
      return Tag::Ptr();
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

    if (normalized_tag_name.empty())
      throw sharp::Exception ("TagManager.GetOrCreateTag () called with an empty tag name.");

    // BEGIN NASTY HACK
    // nasty hack to make things work
    // force making of a tag even if we have one all ready
    Tag::Ptr t(new Tag(tag_name));
    m_internal_tags [ t->normalized_name() ] = t;
    m_tag_map [ t->normalized_name() ] = t;
    return t;
    //return Tag::Ptr();
    // END NASTY HACK
    //FRED
    // FIXME: Get rid of next line and debug below...
    //return Tag::Ptr();

    std::vector<std::string> splits;
    sharp::string_split(splits, normalized_tag_name, ":");
    // BEGIN if ((splits.size() > 2) 
    if ((splits.size() > 2) || KTGlib::str_has_prefix(normalized_tag_name, Tag::SYSTEM_TAG_PREFIX)){
	std::map<std::string, Tag::Ptr>::const_iterator iter = m_internal_tags.find(normalized_tag_name);

      if(iter != m_internal_tags.end()) {
        return iter->second;
      }
      else {
        Tag::Ptr t(new Tag(tag_name));
        m_internal_tags [ t->normalized_name() ] = t;
        return Tag::Ptr();
      }
    } // END if ((splits.size() > 2) 

   Tag::Ptr tag = get_tag (normalized_tag_name);

   // FIXME: NEED A RAFT OF ERROR HANDLING FROM GNOTE
   if(!tag){
	std::cout << "TagManager::get_or_create_tag(): FIXME: CAN'T MAKE TAG" << normalized_tag_name << std::endl;
   }

   return tag;
}
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
Tag::Ptr TagManager::get_or_create_system_tag (const std::string & tag_name) {
    return get_or_create_tag(Tag::SYSTEM_TAG_PREFIX + tag_name);
}

// BEGIN TagManager::remove_tag ()
// <summary>
// This will remove the tag from every note that is currently tagged
// and from the main list of tags.
// </summary>
void TagManager::remove_tag (const Tag::Ptr & tag) {
    if (!tag){
      std::cout << "TagManager.RemoveTag () called with a null tag";
      return;
    }

    if(tag->is_property() || tag->is_system()){
      m_internal_tags.erase(tag->normalized_name());
    }

    // typedef std::map<std::string, Tag::Ptr> TagMap;

    bool tag_removed = false;
    TagMap::iterator map_iter;
    map_iter = m_tag_map.find(tag->normalized_name());
    if (map_iter != m_tag_map.end()) {
      map_iter = m_tag_map.find(tag->normalized_name());
      if (map_iter != m_tag_map.end()) {
        Tag::Ptr iter = map_iter->second;
        if (!m_tags->erase(iter)) {
          std::cout << "TagManager: Removed tag: %s", tag->normalized_name().c_str();
        } 
        else { 
          // FIXME: For some really weird reason, this block actually gets called sometimes!
          std::cout << "TagManager: Call to remove tag from ListStore failed: %s", tag->normalized_name().c_str();
        }

        m_tag_map.erase(map_iter);
        std::cout << "Removed TreeIter from tag_map: %s", tag->normalized_name().c_str();
        tag_removed = true;

        std::list<Note*> notes;
        tag->get_notes(notes);
        for(std::list<Note*>::const_iterator note_iter = notes.begin();
            note_iter != notes.end(); ++note_iter) {
          (*note_iter)->remove_tag(tag);
        }
      }
    }

    return;
} // END TagManager::remove_tag ()
  
void TagManager::all_tags(std::list<Tag::Ptr> & tags) const {
  // FIXME: UNCOMMENT IMPLEMENT
  // Add in the system tags first
  // sharp::map_get_values(m_internal_tags, tags);

  TagMap::const_iterator iter = m_tag_map.begin();

	if (m_tag_map.empty()) return;
    // Now all the other tags
    for(TagMap::const_iterator iter = m_tag_map.begin();
        iter != m_tag_map.end(); ++iter) {
      	Tag::Ptr tag;
      	// FIXME: NEED TO TEST
      	//iter->second->get_value(0, tag);      
      	tag = iter->second;
         
     	tags.push_back(tag);
    }
} // END TagManager::all_tags()
} // namespace gnote 
