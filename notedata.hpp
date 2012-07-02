#ifndef __NOTE_DATA_HPP_
#define __NOTE_DATA_HPP_

#include <string>

#include "datetime.hpp"

namespace gnote {
class NoteData
{
/* This holds the actual data, text, and on on of the note */
  public:
    NoteData(const std::string & _uri);
    std::string       m_text;

    const std::string & full_path() const
      {
        return m_full_path;
      }

    const std::string & uri() const
      {
        return m_uri;
      }

    const std::string & title() const
      {
        return m_title;
      }
    std::string & title()
      {
        return m_title;
      }
    const std::string & text() const
      { 
        return m_text;
      }
    std::string & text()
      { 
        return m_text;
      }
    const sharp::DateTime & create_date() const
      {
        return m_create_date;
      }
    sharp::DateTime & create_date()
      {
        return m_create_date;
      }
    const sharp::DateTime & change_date() const
      {
        return m_change_date;
      }

    void set_change_date(const sharp::DateTime & date)
      {
        m_change_date = date;
        m_metadata_change_date = date;
      }

    void set_full_path(const std::string & path)
      {
        m_full_path = path;
      }

    const sharp::DateTime & metadata_change_date() const
      {
        return m_metadata_change_date;
      }
    sharp::DateTime & metadata_change_date()
      {
        return m_metadata_change_date;
      }
    int cursor_position() const
      {
        return m_cursor_pos;
      }
    void set_cursor_position(int new_pos)
      {
        m_cursor_pos = new_pos;
      }
    int width() const
      {
        return m_width;
      }
    int & width()
      {
        return m_width;
      }
    int height() const
      {
        return m_height;
      }
    int & height()
      {
        return m_height;
      }
    int x() const
      {
        return m_x;
      }
    int & x()
      {
        return m_x;
      }
    int y() const
      {
        return m_y;
      }
    int & y()
      {
        return m_y;
      }
    
    bool is_open_on_startup() const
      {
        return m_open_on_startup;
      }
    void set_is_open_on_startup(bool v)
      {
        m_open_on_startup = v;
      }
    void set_position_extent(int x, int y, int width, int height);
    bool has_position();
    bool has_extent();

  private:
    const std::string m_uri;
    std::string       m_title;
    std::string       m_full_path; // full path to the note
    sharp::DateTime             m_create_date;
    sharp::DateTime             m_change_date;
    sharp::DateTime             m_metadata_change_date;
    int               m_cursor_pos;
    int               m_width, m_height;
    int               m_x, m_y;
    bool              m_open_on_startup;
    static const int  s_noPosition;
}; // class NoteData
} //  namespace gnote 
#endif // __NOTE_DATA_HPP_
