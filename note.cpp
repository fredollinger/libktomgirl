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

#include "config.h"

#include <tr1/functional>

// BEGIN BOOST INCLUDES
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/find.hpp>
// END BOOST INCLUDES

#include <libxml/parser.h>

// BEGIN STD INCLUDES
#include <map>
#include <iostream>
// BEGIN STD INCLUDES

#include "datetime.hpp"
#include "debug.hpp"
#include "files.hpp"
#include "note.hpp"
#include "notedata.hpp"
#include "notebuffer.hpp"
#include "notemanager.hpp"
#include "tag.hpp"
#include "tagmanager.hpp"
#include "string.hpp"
#include "xmlconvert.hpp"
#include "xmlreader.hpp"
#include "xmlwriter.hpp"

namespace utils{
    std::string encode(const std::string & source)
    {
      sharp::XmlWriter xml;
      xml.write_string(source);

      xml.close();
      return xml.to_string();
    }


    std::string decode(const std::string & source)
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
}

namespace gnote{
// BEGIN NOTE
Note::Note(NoteData * _data, const std::string & filepath, NoteManager & _manager)
    : m_text_content("")
    , m_data(_data)
    , m_filepath(filepath)
    , m_save_needed(false)
    , m_is_deleting(false)
    , m_manager(_manager)
    , m_is_open(false)
{
}

Note::~Note()
{
	//std::cout << "~Note()" <<  m_filepath << std::end;
}

/* Reload the note. */
void Note::reload(){
    NoteData *data = NoteArchiver::read(m_filepath, url_from_path(m_filepath));
}

void Note::changed(){
    m_save_needed = true;
}

  const std::string & Note::uri() const
  {
    return m_data.data().uri();
  }


  const std::string & Note::get_title() const
  {
    //return m_title;
    return m_data.getData().title();
  }

/*  Parse guid from file path.
 *  We assume that the filepath + guid + ".note" is the m_fullpath.
 *  If this changes then obviously we break this... 
 */
std::string Note::uid() const {
	size_t len = m_filepath.length();
	size_t begin = m_filepath.find_last_of("/");
	return m_filepath.substr(begin+1, len - 6 - begin);
}

Note::Ptr Note::create_existing_note(NoteData *data,
                                 std::string filepath,
                                 NoteManager & manager)
{
    if (!data->change_date().is_valid()) {
      sharp::DateTime d(boost::filesystem::last_write_time(filepath));
      data->set_change_date(d);
    }
    if (!data->create_date().is_valid()) {
      if(data->change_date().is_valid()) {
        data->create_date() = data->change_date();
      }
      else {
        sharp::DateTime d(boost::filesystem::last_write_time(filepath));
        data->create_date() = d;
      }
    }
    return Note::Ptr(new Note(data, filepath, manager));
}

  /// <summary>
  /// Returns a Tomboy URL from the given path.
  /// </summary>
  /// <param name="filepath">
  /// A <see cref="System.String"/>
  /// </param>
  /// <returns>
  /// A <see cref="System.String"/>
  /// </returns>
  std::string Note::url_from_path(const std::string & filepath)
  {
    return "note://gnote/" + sharp::file_basename(filepath);
  }

  Note::Ptr Note::load(const std::string & read_file, NoteManager & manager)
  {
    NoteData *data = NoteArchiver::read(read_file, url_from_path(read_file));
    return create_existing_note (data, read_file, manager);
  }

// BEGIN PARSE_TAGS
void Note::parse_tags(const xmlNodePtr tagnodes, std::list<std::string> & tags) {
  sharp::XmlNodeSet nodes = sharp::xml_node_xpath_find(tagnodes, "//*");
    
  if(nodes.empty()) {
    return;
  }

  // BEGIN PARSE_TAGS FOR LOOP
  for(sharp::XmlNodeSet::const_iterator iter = nodes.begin();
      iter != nodes.end(); ++iter) {

        const xmlNodePtr node = *iter;
     if(xmlStrEqual(node->name, (const xmlChar*)"tag") && (node->type == XML_ELEMENT_NODE)) 
     {
        xmlChar * content = xmlNodeGetContent(node);
        if(content) 
        {
          DBG_OUT("found tag %s", content);
          tags.push_back((const char*)content);
          xmlFree(content);
        }
    }
  } // END PARSE_TAGS FOR LOOP
}
// END PARSE_TAGS

std::string Note::text_content(){
	if ( 0 == m_text_content.size()){
				m_text_content=utils::decode(xml_content());
  }

	//std::cout << "std::string Note::text_content(): [" << m_text_content << "]";
	return m_text_content;
}

  void Note::set_text_content(const std::string & text)
  {
    //std::cout << "Note::set_text_content(): [" << text << "]";
    m_data.data().text() = text;
    m_text_content = text;
    return;
  }


// BEGIN Note:set_title()
void Note::set_title(const std::string & new_title)
{
    m_data.data().title() = new_title;
}
// END Note:set_title()


// END NOTE


// BEGIN NOTE ARCHIVER
std::string NoteArchiver::write_string(const NoteData & note)
{
    std::string str;
    sharp::XmlWriter xml;
    obj().write(xml, note);
    xml.close();
    str = xml.to_string();
    return str;
}


void Note::write(const std::string & _write_file, const NoteData & note)
{
    return;
}

  void NoteArchiver::write(const std::string & write_file, const NoteData & data)
{
    obj().write_file(write_file, data);
}

// BEGIN NoteArchiver::write_file()
void NoteArchiver::write_file(const std::string & _write_file, const NoteData & note)
{
    std::string tmp_file = _write_file + ".tmp";
    // TODO Xml doc settings
    sharp::XmlWriter xml(tmp_file); //, XmlEncoder::DocumentSettings);
    write(xml, note);
    xml.close ();

    try {
      if (boost::filesystem::exists(_write_file)) {
        std::string backup_path = _write_file + "~";
        if (boost::filesystem::exists(backup_path)) {
          boost::filesystem::remove(backup_path);
        }
      
        // Backup the to a ~ file, just in case
        boost::filesystem::rename(_write_file, backup_path);
      
        // Move the temp file to write_file
        boost::filesystem::rename(tmp_file, _write_file);

        // Delete the ~ file
        boost::filesystem::remove(backup_path);
      } 
      else {
        // Move the temp file to write_file
        boost::filesystem::rename(tmp_file, _write_file);
      }
    }
    catch(const std::exception & e)
    {
		  std::cout << "ERROR: NoteArchiver::write_file(): save fail." << std::endl;
    }
  } // END NoteArchiver::write_file()

// FIXME: FRED: add tag support
// BEGIN NOTEARCHIVER::WRITE
void NoteArchiver::write(sharp::XmlWriter & xml, const NoteData & note)
{
    xml.write_start_document();
    xml.write_start_element("", "note", "http://beatniksoftware.com/tomboy");
    xml.write_attribute_string("",
                             "version",
                             "",
                             CURRENT_VERSION);
    xml.write_attribute_string("xmlns",
                             "link",
                             "",
                             "http://beatniksoftware.com/tomboy/link");
    xml.write_attribute_string("xmlns",
                             "size",
                             "",
                             "http://beatniksoftware.com/tomboy/size");

    xml.write_start_element ("", "title", "");
    xml.write_string (note.title());
    xml.write_end_element ();

    xml.write_start_element ("", "text", "");
    xml.write_attribute_string ("xml", "space", "", "preserve");
    // Insert <note-content> blob... BLOB
    // FIXME: let's eventually try to get this to work:

   xml.write_raw (NoteBufferArchiver::serialize(note.text()));
    // for now we'll do this...
    //xml.write_raw (note.text_plain());

    xml.write_end_element ();

    xml.write_start_element ("", "last-change-date", "");
    xml.write_string (
      sharp::XmlConvert::to_string (note.change_date()));
    xml.write_end_element ();

    xml.write_start_element ("", "last-metadata-change-date", "");
    xml.write_string (
      sharp::XmlConvert::to_string (note.metadata_change_date()));
    xml.write_end_element ();

    if (note.create_date().is_valid()) {
      xml.write_start_element ("", "create-date", "");
      xml.write_string (
        sharp::XmlConvert::to_string (note.create_date()));
      xml.write_end_element ();
    }

    xml.write_start_element ("", "cursor-position", "");
    xml.write_string (boost::lexical_cast<std::string>(note.cursor_position()));
    xml.write_end_element ();

    xml.write_start_element ("", "width", "");
    xml.write_string (boost::lexical_cast<std::string>(note.width()));
    xml.write_end_element ();

    xml.write_start_element("", "height", "");
    xml.write_string(boost::lexical_cast<std::string>(note.height()));
    xml.write_end_element();

    xml.write_start_element("", "x", "");
    xml.write_string (boost::lexical_cast<std::string>(note.x()));
    xml.write_end_element();

    xml.write_start_element ("", "y", "");
    xml.write_string (boost::lexical_cast<std::string>(note.y()));
    xml.write_end_element();

    // BEGIN DEPRECATED
    #if 0
    if (note.tags().size() > 0) 
	    std::cout << "NoteArchiver::write(): have tags!\n";
    else
	    std::cout << "NoteArchiver::write(): have NO tags!\n";
    #endif
    // END DEPRECATED
	
    if (note.tags().size() > 0) {
      xml.write_start_element ("", "tags", "");
      for(NoteData::TagMap::const_iterator iter = note.tags().begin();
        iter != note.tags().end(); ++iter) {
        xml.write_start_element("", "tag", "");
        xml.write_string(iter->second->name());
        xml.write_end_element();
      }
      xml.write_end_element();
    }

    xml.write_start_element("", "open-on-startup", "");
    xml.write_string(note.is_open_on_startup() ? "True" : "False");
    xml.write_end_element();

    xml.write_end_element(); // Note
    xml.write_end_document();

}
// END WRITE()
 
  const char *NoteArchiver::CURRENT_VERSION = "0.3";
//  const char *NoteArchiver::DATE_TIME_FORMAT = "%Y-%m-%dT%T.@7f@%z"; //"yyyy-MM-ddTHH:mm:ss.fffffffzzz";

  NoteData *NoteArchiver::read(const std::string & read_file, const std::string & uri)
  {
    return obj()._read(read_file, uri);
  }


// BEGIN NoteArchiver::_read()
NoteData *NoteArchiver::_read(const std::string & read_file, const std::string & uri)
{
    NoteData *note = new NoteData(uri);
    std::string version;

    sharp::XmlReader xml(read_file);

    std::string name;

    while (xml.read ()) {
      switch (xml.get_node_type()) {
      case XML_READER_TYPE_ELEMENT:
        name = xml.get_name();
        
        if(name == "note") {
          version = xml.get_attribute("version");
        }
        else if(name == "title") {
          note->title() = xml.read_string();
        } 
        else if(name == "text") {
          // <text> is just a wrapper around <note-content>
          // NOTE: Use .text here to avoid triggering a save.
          note->text() = xml.read_inner_xml();
        }
        else if(name == "last-change-date") {
          note->set_change_date(
            sharp::XmlConvert::to_date_time (xml.read_string()));
        }
        else if(name == "last-metadata-change-date") {
          note->metadata_change_date() =
            sharp::XmlConvert::to_date_time(xml.read_string());
        }
        else if(name == "create-date") {
          note->create_date() =
            sharp::XmlConvert::to_date_time (xml.read_string());
        }
        else if(name == "cursor-position") {
          note->set_cursor_position(boost::lexical_cast<int>(xml.read_string()));
        }
        else if(name == "width") {
          note->width() = boost::lexical_cast<int>(xml.read_string());
        }
        else if(name == "height") {
          note->height() = boost::lexical_cast<int>(xml.read_string());
        }
        else if(name == "x") {
          note->x() = boost::lexical_cast<int>(xml.read_string());
        }
        else if(name == "y") {
          note->y() = boost::lexical_cast<int>(xml.read_string());
        }
        else if(name == "tags") {
          xmlDocPtr doc2 = xmlParseDoc((const xmlChar*)xml.read_outer_xml().c_str());
// FRED FIX AND UNCOMMENT
          if(doc2) {
            std::list<std::string> tag_strings;
            Note::parse_tags(doc2->children, tag_strings);
            for(std::list<std::string>::const_iterator iter = tag_strings.begin();
                iter != tag_strings.end(); ++iter) {
	      // FRED: FIXME:
               Tag::Ptr tag = TagManager::obj().get_or_create_tag(*iter);
               note->tags()[tag->normalized_name()] = tag;
            }
            xmlFreeDoc(doc2);
          }
          else {
            DBG_OUT("loading tag subtree failed");
          }
        }

        else if(name == "open-on-startup") {
          note->set_is_open_on_startup(xml.read_string() == "True");
        }
        break;

      default:
        break;
      }
    }
    xml.close ();

    if (version != NoteArchiver::CURRENT_VERSION) {
      // Note has old format, so rewrite it.  No need
      // to reread, since we are not adding anything.
      DBG_OUT("Updating note XML from %s to newest format...", version.c_str());
      NoteArchiver::write (read_file, *note);
    }
    return note;
  }
// END NoteArchiver::_read()
// END NOTE ARCHIVER

// BEGIN NoteDataBufferSynchronizer
  NoteDataBufferSynchronizer::~NoteDataBufferSynchronizer()
  {
    delete m_data;
  }

  const std::string & NoteDataBufferSynchronizer::text()
  {
    //synchronize_text();

    //return NoteBufferArchiver::serialize(m_data->text());
    return m_data->text();
  }

  void NoteDataBufferSynchronizer::set_text(const std::string & t)
  {
    m_data->text() = t;
    synchronize_buffer();
  }

  void NoteDataBufferSynchronizer::invalidate_text()
  {
    m_data->text() = "";
  }

  bool NoteDataBufferSynchronizer::is_text_invalid() const
  {
    return m_data->text().empty();
  }

/*
  void NoteDataBufferSynchronizer::synchronize_text(std::string &text) const
  {
	m_data->text() = text;
  }
*/

void NoteDataBufferSynchronizer::synchronize_buffer()
{
}

  void NoteDataBufferSynchronizer::buffer_changed()
  {
    invalidate_text();
  }
// END NoteDataBufferSynchronizer

/*
const NoteData & NoteData::synchronized_data() const
{
      return *m_data;
}
*/
  
void Note::save()
{
      NoteArchiver::write(m_filepath, m_data.synchronized_data());
}

#if 0
void Note::set_text(const std::string & t)
{
    m_data->text() = t;
    //synchronize_buffer();
}
#endif

//void NoteDataBufferSynchronizer::synchronize_text() const
//      m_data->text() = NoteBufferArchiver::serialize(m_data->text());
/*
  {
    if(is_text_invalid() && m_buffer) {
      m_data->text() = NoteBufferArchiver::serialize(m_buffer);
    }
*/
    	//m_text = NoteBufferArchiver::serialize(s);
    	//m_text = NoteBufferArchiver::serialize(neu);
 //   }

  /// <summary>
  /// Creates a New Note with the given values.
  /// </summary>
  /// <param name="title">
  /// A <see cref="System.String"/>
  /// </param>
  /// <param name="filepath">
  /// A <see cref="System.String"/>
  /// </param>
  /// <param name="manager">
  /// A <see cref="NoteManager"/>
  /// </param>
  /// <returns>
  /// A <see cref="Note"/>
  /// </returns>

Note::Ptr Note::create_new_note(const std::string & title,
                                  const std::string & filename,
                                  NoteManager & manager)
{
    NoteData * note_data = new NoteData(url_from_path(filename));
    note_data->title() = title;
    // We set text content, initially to be the same as the title so it shows
    // up.
    note_data->text() = title;

    // BEGIN SET DATE
    sharp::DateTime date(sharp::DateTime::now());
    note_data->create_date() = date;
    note_data->set_change_date(date);
    // END SET DATE
      
    return Note::Ptr(new Note(note_data, filename, manager));
}

// BEGIN Note::delete_note()
void Note::delete_note()
{
    m_is_deleting = true;
}
// END Note::delete_note()

  const NoteData & Note::data() const
  {
    return m_data.synchronized_data();
  }

  NoteData & Note::data()
  {
    return m_data.synchronized_data();
  }

   void Note::get_tags(std::list<Tag::Ptr> & l) const
  { 
    sharp::map_get_values(m_data.data().tags(), l);
  } 

  void Note::remove_tag(Tag & tag)
  {
    std::string tag_name = tag.normalized_name();
    NoteData::TagMap & thetags(m_data.data().tags());
    NoteData::TagMap::iterator iter;

    // if we are deleting the note, no need to check for the tag, we 
    // know it is there.
    if(!m_is_deleting) {
      iter = thetags.find(tag_name);
      if (iter == thetags.end())  {
        return;
      }
    }

    // m_signal_tag_removing(*this, tag);

    // don't erase the tag if we are deleting the note. 
    // This will invalidate the iterator.
    // see bug 579839.
    if(!m_is_deleting) {
      thetags.erase(iter);
    }
    tag.remove_note(*this);

    // m_signal_tag_removed(shared_from_this(), tag_name);

    // DBG_OUT("Tag removed, queueing save");
    // queue_save(OTHER_DATA_CHANGED);
  }

  void Note::remove_tag(const Tag::Ptr & tag)
  {
    if (!tag)
      std::cout << "Note.RemoveTag () called with a null tag."<<std::endl;

    remove_tag(*tag);
  }

  bool Note::contains_tag(const Tag::Ptr & tag) const
  {
    const NoteData::TagMap & thetags(m_data.data().tags());
    return (thetags.find(tag->normalized_name()) != thetags.end());
  }

void Note::add_tag(const Tag::Ptr & tag) {
    if(!tag) {
	     std::cout << "note::add_tag() called with a NULL tag.";
	     return;
    }
    tag->add_note (*this);

    NoteData::TagMap & thetags(m_data.data().tags());
    if (thetags.find(tag->normalized_name()) == thetags.end()) {
      thetags[tag->normalized_name()] = tag;

 //     m_signal_tag_added(*this, tag);

//      DBG_OUT ("Tag added, queueing save");
 //     queue_save(OTHER_DATA_CHANGED);
    }
}

} // namespace gnote
// Wed Jun 13 10:03:47 PDT 2012
