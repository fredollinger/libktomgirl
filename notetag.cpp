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


#include <boost/lexical_cast.hpp>

#include "xmlreader.hpp"
#include "xmlwriter.hpp"
#include "debug.hpp"
#include "notetag.hpp"

namespace gnote {
  NoteTag::NoteTag(const std::string & tag_name, int flags) throw(sharp::Exception) 
  {
    if (tag_name.empty()) {
      throw sharp::Exception ("NoteTags must have a tag name.  Use "
                              "DynamicNoteTag for constructing "
                              "anonymous tags.");
    }
    
  }

  
  NoteTag::NoteTag()
  {
  }


  void NoteTag::initialize(const std::string & element_name)
  {
  }

} // namespace gnote

