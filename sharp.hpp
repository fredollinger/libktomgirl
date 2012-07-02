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
