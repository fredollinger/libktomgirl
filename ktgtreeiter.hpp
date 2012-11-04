/*
 * KTomGirl
 *
 * TreeIter:
 * 
 * Iterator class to simulate GTK::TreeIter.
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

#ifndef _KTG_TREE_ITER_HPP_
#define _KTG_TREE_ITER_HPP_



namespace KTGlib {
class Tree;
class TreeIter{
public:
	TreeIter(void);
	TreeIter(Tree*);
	void setCount(int);

protected:
	Tree *model;
	int m_count;
	bool is_end;


}; // END class TreeIter
}  // namespace KTGlib
#endif // _KTG_TREE_ITER_HPP_
// Sun Nov  4 14:24:23 PST 2012
