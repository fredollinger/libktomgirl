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



#ifndef __NOTE_TAG_HPP_
#define __NOTE_TAG_HPP_

#include <string>
#include <map>
#include <memory>
#include <tr1/memory>

#include "exception.hpp"

namespace sharp {
  class XmlWriter;
  class XmlReader;
}

namespace gnote {
class NoteTag{
public:
  typedef std::auto_ptr <NoteTag> Ptr;
  typedef std::auto_ptr <const NoteTag> ConstPtr;

  enum TagFlags {
    NO_FLAG       = 0,
    CAN_SERIALIZE = 1,
    CAN_UNDO      = 2,
    CAN_GROW      = 4,
    CAN_SPELL_CHECK = 8,
    CAN_ACTIVATE  = 16,
    CAN_SPLIT     = 32
  };

  static Ptr create(const std::string & tag_name, int flags) throw(sharp::Exception)
    {
      return Ptr(new NoteTag(tag_name, flags));
    }

protected:
  NoteTag(const std::string & tag_name, int flags = 0) throw(sharp::Exception);
  NoteTag();
  virtual void initialize(const std::string & element_name);

};
}
#endif
