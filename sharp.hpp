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


#ifndef _SHARP_HPP__
#define _SHARP_HPP__

/* sharp
 * drop-in replacement for all things sharp
 */

#include <list>
#include <string>

namespace sharp{

bool directory_exists(const std::string & directory);

void directory_get_files(const std::string & dir, std::list<std::string>  & files);

void directory_get_files_with_ext(const std::string & dir,
                                    const std::string & ext,
                                    std::list<std::string> & list);

std::string std_string_to_lower(const std::string & source);

} // namespace sharp 
#endif
