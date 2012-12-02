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

#include <iostream>

namespace KTGlib {
Tree::Tree()
	: m_count(0) 
{
}

// COPY
KTGlib::Tree::Tree(const KTGlib::Tree &t){
/*
	std::map<std::string, KTGlib::TreeIter>::const_iterator begin = t.m_tree.begin();
	std::map<std::string, KTGlib::TreeIter>::const_iterator end = t.m_tree.end();
	m_tree = std::map<std::string, KTGlib::TreeIter>(begin, end);
*/
}

// COPY
KTGlib::Tree::Tree(const KTGlib::Tree *t){
	/*
	std::map<std::string, KTGlib::TreeIter>::const_iterator begin = t->m_tree.begin();
	std::map<std::string, KTGlib::TreeIter>::const_iterator end = t->m_tree.end();
	m_tree = std::map<std::string, KTGlib::TreeIter>(begin, end);
	*/
}

TreeIter Tree::append(const std::string &st){
	m_count++;
	TreeIter itr;
	itr.setCount(m_count);	
	m_tree[st]=itr;
	return itr;
}

TreeIter Tree::append(){
	return append("");
}

TreeIter Tree::find(std::string st){
	TreeIter iter(KTGLIB_TREE_ITER_TYPE_END);
	std::cout << "Tree::find(): "<< st;
	m_tree.find(st);
	if (m_tree.find(st) != m_tree.end())
		return m_tree[st];	
	return iter;
}

TreeIter Tree::begin(){
	return TreeIter(KTGLIB_TREE_ITER_TYPE_BEGIN);
}

TreeIter Tree::end(){
	return TreeIter(KTGLIB_TREE_ITER_TYPE_END);
}

bool Tree::operator=(TreeIter ti){
	// FIXME STUB
	return true;
}

//home/follinge/projects/libktomgirl/tagmanager.cpp :185: error: no matching function for call to 'KTGlib::Tree::erase(std::tr1::shared_ptr<gnote::Tag>&)'
//home/follinge/projects/libktomgirl/ktgtree.hpp:40: note: candidates are: bool KTGlib::Tree::erase(KTGlib::TreeIter)
bool KTGlib::Tree::erase(std::tr1::shared_ptr<gnote::Tag> &tag){
  TreeMap::iterator iter;
  TreeIter l_ti;
  for (iter = m_tree.begin(); iter != m_tree.end(); iter++) {
    l_ti = iter->second;
    if (tag == *l_ti){
      std::cout << "Tree:erasing: " << iter->first << std::endl;
      m_tree.erase(iter); 
      return true;
    } 
  }
  return false;
}

} // namespace KTGlib 
// Sun Dec  2 11:25:13 PST 2012
