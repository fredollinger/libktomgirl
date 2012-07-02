/*
 * KTomGirl
 *
 * KTGlib:
 * 
 * A wrapper for Glib, providing the equivalents without glib for KTomGirl Project.
 *
 * Copyright (C) 2012 Fred Ollinger
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

#ifndef _KTG_STRING_HPP_
#define _KTG_STRING_HPP_

#include <list>
#include <string>

#include <boost/cstdint.hpp>

namespace KTGlib {
typedef std::list<std::string> StringList;
typedef boost::uint64_t gunichar; 
bool str_has_prefix(std::string, const char *);

std::string build_filename(const std::string & p, const std::string & fn);

std::string get_user_data_dir();

// BEGIN class ustring 
class ustring{
public:
  ustring();
  ustring(std::string);
  ~ustring();
  const char* c_str();

private:
  std::string m_qs;
}; // END class ustring
}  // namespace KTGlib
#endif
// Tue Mar 27 20:32:49 PDT 2012
