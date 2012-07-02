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
