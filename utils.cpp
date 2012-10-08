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


#include <iostream>
#include <algorithm>

#include <boost/format.hpp>
#include <boost/bind.hpp>

#include "xmlreader.hpp"
#include "xmlwriter.hpp"
#include "string.hpp"
#include "datetime.hpp"
#include "note.hpp"
#include "utils.hpp"

namespace gnote {
  namespace utils {
    std::string XmlEncoder::encode(const std::string & source)
    {
      sharp::XmlWriter xml;
      xml.write_string(source);

      xml.close();
      return xml.to_string();
    }


    std::string XmlDecoder::decode(const std::string & source)
    {
      // TODO there is probably better than a std::string for that.
      // this will do for now.
      std::string builder;

      sharp::XmlReader xml;
      xml.load_buffer(source);

      while (xml.read ()) {
        switch (xml.get_node_type()) {
        case XML_READER_TYPE_TEXT:
        case XML_READER_TYPE_WHITESPACE:
          builder += xml.get_value();
          break;
        default:
          break;
        }
      }

      xml.close ();

      return builder;
    }

    

  }  // namespace utils 
} // namespace gnote 
// Sun Oct  7 17:11:37 PDT 2012
