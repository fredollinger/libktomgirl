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

#ifndef __PREFERENCES_HPP_
#define __PREFERENCES_HPP_

#include <string>

#include "base/singleton.hpp"

namespace gnote {

  class Preferences 
    : public base::Singleton<Preferences>
  {
  public:
    static const char *ENABLE_SPELLCHECKING;
    static const char *ENABLE_WIKIWORDS;
    static const char *ENABLE_CUSTOM_FONT;
    static const char *ENABLE_KEYBINDINGS;
    static const char *ENABLE_STARTUP_NOTES;
    static const char *ENABLE_AUTO_BULLETED_LISTS;
    static const char *ENABLE_ICON_PASTE;
    static const char *ENABLE_CLOSE_NOTE_ON_ESCAPE;

    static const char *START_NOTE_URI;
    static const char *CUSTOM_FONT_FACE;
    static const char *MENU_NOTE_COUNT;
    static const char *MENU_PINNED_NOTES;

    static const char *KEYBINDING_SHOW_NOTE_MENU;
    static const char *KEYBINDING_OPEN_START_HERE;
    static const char *KEYBINDING_CREATE_NEW_NOTE;
    static const char *KEYBINDING_OPEN_SEARCH;
    static const char *KEYBINDING_OPEN_RECENT_CHANGES;

    static const char *EXPORTHTML_LAST_DIRECTORY;
    static const char *EXPORTHTML_EXPORT_LINKED;
    static const char *EXPORTHTML_EXPORT_LINKED_ALL;

    static const char *SYNC_CLIENT_ID;
    static const char *SYNC_LOCAL_PATH;
    static const char *SYNC_SELECTED_SERVICE_ADDIN;
    static const char *SYNC_CONFIGURED_CONFLICT_BEHAVIOR;

    static const char *INSERT_TIMESTAMP_FORMAT;
    
    static const char *SEARCH_WINDOW_X_POS;
    static const char *SEARCH_WINDOW_Y_POS;
    static const char *SEARCH_WINDOW_WIDTH;
    static const char *SEARCH_WINDOW_HEIGHT;
    static const char *SEARCH_WINDOW_SPLITTER_POS;

    Preferences();
    ~Preferences();
};
}
#endif
