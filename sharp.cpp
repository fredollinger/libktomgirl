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

#include <string>

#include "sharp.hpp"

#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace sharp{

std::string std_string_to_lower(const std::string & source)
{
    return boost::to_lower_copy(source);
}

void directory_get_files_with_ext(const std::string & dir, 
                                    const std::string & ext,
                                    std::list<std::string> & list) {
    boost::filesystem::path p(dir);
    
    if(!exists(p)) {
      return;
    }
    boost::filesystem::directory_iterator end_itr; 
    for ( boost::filesystem::directory_iterator itr( p );
          itr != end_itr;
          ++itr )
    {
      // is_regular() is deprecated but is_regular_file isn't in 1.34.
      if ( is_regular(*itr) && (ext.empty() || (std_string_to_lower(extension(*itr)) == ext)) )
      {
        list.push_back(itr->string());
      }
    }
  }

void directory_get_files(const std::string & dir, std::list<std::string>  & files) {
    directory_get_files_with_ext(dir, "", files);
}

bool directory_exists(const std::string & dir) {
    boost::filesystem::path p(dir);
    return (exists(p) && is_directory(p));
}

} // namespace sharp
