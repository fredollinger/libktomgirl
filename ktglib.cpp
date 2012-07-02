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

#include "ktglib.hpp"

namespace KTGlib {
ustring::ustring() : m_qs() {}
ustring::~ustring() {}
ustring::ustring(std::string st) : m_qs(st) {}

const char* ustring::c_str(){
  return m_qs.c_str();
}

bool str_has_prefix(std::string st, const char *ch){
	size_t found;

	found = st.find_first_of(ch);
	if (0 == found)
		return true;

	return false;
}

std::string get_user_data_dir(){ 
	return getenv("HOME") + std::string("/.local/share");
}

std::string build_filename(const std::string & p, const std::string & fn)
{
	return p + "/" + fn;
}

} // namespace KTGlib
