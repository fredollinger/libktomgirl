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

#include <algorithm>
#include <tr1/array>


#include "../libtomgirl/debug.hpp"
#include "notebuffer.hpp"
#include "note.hpp"
#include "preferences.hpp"

#include "xmlreader.hpp"
#include "xmlwriter.hpp"

namespace gnote {

#define NUM_INDENT_BULLETS 3

  NoteBuffer::NoteBuffer(Note & note) :
     m_note(note)
  {
  }

  NoteBuffer::~NoteBuffer()
  {
  }

#if 0
  std::string NoteBufferArchiver::serialize(const Glib::RefPtr<Gtk::TextBuffer> & buffer, 
                                            const Gtk::TextIter & end)
  {
    sharp::XmlWriter xml;
    
    serialize(buffer, start, end, xml);
    xml.close();
    std::string serializedBuffer = xml.to_string();
    // FIXME: there is some sort of attempt to ensure the endline are the
    // same on all platforms.
    return serializedBuffer;
  }
#endif

  
// FIXME: We do nothing yet...
// BEGIN NoteBufferArchiver::serialize()
// This is taken almost directly from GAIM.  There must be a
// better way to do this...
std::string NoteBufferArchiver::serialize(const std::string &str)
{
    sharp::XmlWriter xml;

    xml.write_start_element ("", "note-content", "");
    xml.write_attribute_string ("", "version", "", "0.1");
    xml.write_attribute_string("xmlns",
                               "link",
                               "",
                               "http://beatniksoftware.com/tomboy/link");
    xml.write_attribute_string("xmlns",
                               "size",
                               "",
                               "http://beatniksoftware.com/tomboy/size");

    xml.write_string(str);

    xml.write_end_element (); // </note-content>
    xml.close();
    std::string serializedBuffer = xml.to_string();
    // FIXME: there is some sort of attempt to ensure the endline are the
    // same on all platforms.
    return serializedBuffer;
}
// END NoteBufferArchiver::serialize()

} // namespace gnote
