/*
 * gnote
 *
 * Copyright (C) 2010 Debarshi Ray
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

#include "config.h"

#include <stdlib.h>

#include <iostream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include "actionmanager.hpp"
#include "ktglib.hpp"
#include "note.hpp"
#include "gnote.hpp"

namespace gnote {

  bool Gnote::s_tray_icon_showing = false;

  Gnote::Gnote()
    : m_manager(NULL)
    , m_is_panel_applet(false)
    , m_prefsdlg(NULL)
  {
	// FIXME: Need to implement settings
	// settings = new KTGSettings("ktomgirl", KTGSettings::NativeFormat);
  }

  Gnote::~Gnote()
  {
    delete m_prefsdlg;
  }


int Gnote::main(int argc, char **argv)
{
    GnoteCommandLine cmd_line;

    // cmd_line.parse(argc, argv);

    m_is_panel_applet = cmd_line.use_panel_applet();

#ifdef ENABLE_DBUS
    if(cmd_line.needs_execute()) {
      cmd_line.execute();
      return 0;
    }
#endif

    ActionManager & am(ActionManager::obj());
    am.load_interface();

#ifndef ENABLE_DBUS
    if(cmd_line.needs_execute()) {
      cmd_line.execute();
    }
#endif

    if(m_is_panel_applet) {
      s_tray_icon_showing = true;
      return 0;

    }
    else {
      //register session manager restart
      start_tray_icon();
    }
    return 0;
  }

void Gnote::start_tray_icon(){
	return;
}

GnoteCommandLine::GnoteCommandLine(){
}
GnoteCommandLine::~GnoteCommandLine(){
}

int GnoteCommandLine::execute(void){
	return 0;
}

bool GnoteCommandLine::use_panel_applet() const{
	return true;
}

bool gnote::GnoteCommandLine::needs_execute() const{
	return true;
}

std::string Gnote::data_dir()
{
	return KTGlib::get_user_data_dir() + "/ktomgirl";
}

std::string Gnote::gnote_data_dir(){
	return KTGlib::get_user_data_dir() + "/gnote";
}

// get the data dir for tomboy
std::string Gnote::tomboy_data_dir(){
	return KTGlib::get_user_data_dir() + "/tomboy";
}

#if 0
// FIXME: Need to get rid of qt only
//KTGlib::StringList Gnote::get_note_list(){

	#if 0
	for (directory_iterator itr(p); itr!=directory_iterator(); ++itr)
	{
		cout << itr->path().filename() << ' '; // display filename only

		if (is_regular_file(itr->status())) cout << " [" << file_size(itr->path()) << ']';
	}
	#endif
	
	//KTGlib::StringList qsl(qdTomboy.entryList());
	return qsl;
}
#endif

// FIXME: Need to get rid of qt only
//KTGlib::StringList Gnote::get_note_list2(){
//void Gnote::get_note_list2(){
KTGlib::StringList Gnote::get_note_list(){
	std::string p = tomboy_data_dir();
	std::string fn;
	KTGlib::StringList qsl;

	// boost::filesystem::directory_iterator itr(p);

	for (boost::filesystem::directory_iterator itr(p); itr!=boost::filesystem::directory_iterator(); ++itr)
	{
		fn = itr->path().filename();
//		std::cout << fn << ' '; // display filename only

		if (is_regular_file(itr->status())){
//			std::cout << " [" << file_size(itr->path()) << ']';
			qsl.push_back(fn);
		}
	}
	
	return qsl;
}

} // namespace gnote
// Sat Jun 23 12:09:47 PDT 2012
