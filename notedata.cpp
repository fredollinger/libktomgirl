
#include "note.hpp"
#include "notedata.hpp"

namespace gnote {
  const int  NoteData::s_noPosition = -1;

  NoteData::NoteData(const std::string & _uri)
    : m_uri(_uri)
    , m_cursor_pos(0)
    , m_width(0)
    , m_height(0)
    , m_x(s_noPosition)
    , m_y(s_noPosition)
    , m_open_on_startup(false)
  {
  }


  void NoteData::set_position_extent(int _x, int _y, int _width, int _height)
  {
    if (_x < 0 || _y < 0)
      return;
    if (_width <= 0 || _height <= 0)
      return;

    m_x = _x;
    m_y = _y;
    m_width = _width;
    m_height = _height;
  }

  bool NoteData::has_position()
  {
    return (m_x != s_noPosition) && (m_y != s_noPosition);
  }

  bool NoteData::has_extent()
  {
    return (m_width != 0) && (m_height != 0);

  }
} // namespace gnote 
// END NOTEDATA
// Sat Jun  2 07:59:33 PDT 2012
