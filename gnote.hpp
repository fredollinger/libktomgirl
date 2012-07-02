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

#ifndef _GNOTE_HPP_
#define _GNOTE_HPP_

#include <string>

#include "base/singleton.hpp"

#include "ktglib.hpp"


namespace gnote {
class PreferencesDialog;
class NoteManager;
class RemoteControl;
class IKeybinder;

class Gnote
  : public base::Singleton<Gnote>
{
public:
  Gnote();
  ~Gnote();
  int main(int argc, char **argv);
  NoteManager & default_note_manager()
    {
      return *m_manager;
    }

  void setup_global_actions();
  void start_tray_icon();
  bool check_tray_icon_showing();

  void on_new_note_action();
  void on_quit_gnote_action();
  void on_preferences_response(int res);
  void on_show_preferences_action();
  void on_show_help_action();
  void on_show_about_action();
  void open_search_all();
  void open_note_sync_window();

// BEGIN STATIC PUBLIC GNOTE FUNCTIONS
  static std::string cache_dir();
  static std::string conf_dir();
  static std::string data_dir();
  static std::string gnote_data_dir();
  static std::string tomboy_data_dir();
  static std::string old_note_dir();
  static KTGlib::StringList get_note_list();
// END STATIC PUBLIC GNOTE FUNCTIONS

private:
  // void start_note_created(const Note::Ptr & start_note);
  void register_remote_control(NoteManager & manager);

  std::string get_note_path(const std::string & override_path);

  bool m_is_panel_applet;
  bool m_keybinder;
  static bool s_tray_icon_showing;

  NoteManager *m_manager;

  PreferencesDialog *m_prefsdlg;

};

class GnoteCommandLine
{
public:
  GnoteCommandLine();
  ~GnoteCommandLine();
  int execute();
  bool        use_panel_applet() const;
  bool        needs_execute() const;

private:
  void        print_version();

  bool        m_use_panel;
  char *     m_note_path;
  bool        m_do_search;
  std::string m_search;
  bool        m_show_version;
  bool        m_do_new_note;
  std::string m_new_note_name;
  char*      m_open_note;
  bool        m_open_start_here;
  char*      m_highlight_search;

  // depend on m_open_note, set in on_post_parse
  std::string m_open_note_name;
  std::string m_open_note_uri;
  std::string m_open_external_note_path;
}; // class GnoteCommandLine

} // namespace gnote 
#endif
// Tue Mar 27 18:24:12 PDT 2012
