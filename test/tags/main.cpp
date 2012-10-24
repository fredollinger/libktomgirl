#include <QApplication>
#include <QDebug>

#include <string>
#include <iostream>

#include <libktomgirl/datetime.hpp>
#include <libktomgirl/ktglib.hpp>
#include <libktomgirl/notebook.hpp>
//#include <libktomgirl/notemanager.hpp>
#include <libktomgirl/notebookmanager.hpp>
#include <libktomgirl/tag.hpp>
#include <libktomgirl/tagmanager.hpp>

using namespace sharp;
using namespace gnote::notebooks;

int main( int argc, char *argv[] )
{
      KTGlib::TreeIter iter;
      std::list<gnote::Tag::Ptr> tags;
      gnote::TagManager::obj().all_tags(tags);

	#if 0
 for(std::list<Tag::Ptr>::const_iterator tag_iter = tags.begin();
        tag_iter != tags.end(); ++tag_iter) {

        const Tag::Ptr & tag(*tag_iter);
        // Skip over tags that aren't notebooks
        if (!tag->is_system()
            || !Glib::str_has_prefix(tag->name(),
            std::string(Tag::SYSTEM_TAG_PREFIX)
            + Notebook::NOTEBOOK_TAG_PREFIX)) {
          continue;
        }
        Notebook::Ptr notebook(new Notebook (tag));
        iter = m_notebooks->append ();
        iter->set_value(0, notebook);
        m_notebookMap [notebook->get_normalized_name()] = iter;
      } 
      #endif 

      return 0;
}
// Mon Sep  3 16:23:15 PDT 2012
