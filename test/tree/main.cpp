//#include <QApplication>
//#include <QDebug>

#include <string>
#include <iostream>

//#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/tagmanager.hpp>
#include <libktomgirl/ktgtree.hpp>

typedef std::auto_ptr<KTGlib::Tree>     InternalMap;

int main( int argc, char *argv[] )
{
//	InternalMap m_internal_tags;
	KTGlib::Tree  m_internal_tags;
	std::string st = "bob";
	KTGlib::TreeIter iter;
	m_internal_tags.append();
	m_internal_tags.find(st);
	m_internal_tags.find("joe");
	return 0;
}
// Sun Nov  4 09:34:37 PST 2012
