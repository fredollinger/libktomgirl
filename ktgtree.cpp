/*
 * KTomGirl
 *
 * Tree:
 * 
 * Class to simulate GTK::TreeView and more as data containers.
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

#include "ktgtree.hpp"
#include "ktgtreeiter.hpp"

namespace KTGlib {
Tree::Tree(){
}

TreeIter Tree::append(){
	TreeIter itr;
	return itr;
}
} // namespace KTGlib 
// Mon Oct 15 12:36:54 PDT 2012