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

#include "ktgtreeiter.hpp"

namespace KTGlib{ 
TreeIter::TreeIter() 
	: model(0)
	, m_count(0)
	, is_end(false)
{ 
	return;
}

TreeIter::TreeIter(Tree *m) : 
	  model(m)
	, m_count(0)
	, is_end(false)
{
	return;
}

void TreeIter::setCount(int c){
	m_count = c;
	return;
}

void TreeIter::operator++(){
	m_count++;
}

} // namespace KTGlib
// Sun Nov  4 14:24:14 PST 2012
