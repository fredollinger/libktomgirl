/*
 * gnote
 *
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

#ifndef __ACTIONMANAGER_HPP_
#define __ACTIONMANAGER_HPP_

#include <string>
#include <list>

#include "base/singleton.hpp"

namespace gnote {

class ActionManager
  : public base::Singleton<ActionManager>
{
public:
  ActionManager();
  void load_interface(void);

}; // ActionManager
} // namespace gnote
#endif // __ACTIONMANAGER_HPP_
// Sat Mar 17 19:14:42 PDT 2012
