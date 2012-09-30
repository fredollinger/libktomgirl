/*
 * gnote
 *
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

namespace gnote{
  class TrieController
  {
  public:
    TrieController(NoteManager &);
    ~TrieController();

    void update();
    TrieTree<Note::WeakPtr> *title_trie() const
      {
        return m_title_trie;
      }
  private:
    void on_note_added (const Note::Ptr & added);
    void on_note_deleted (const Note::Ptr & deleted);
    void on_note_renamed (const Note::Ptr & renamed, const std::string & old_title);
      
    NoteManager & m_manager;
    TrieTree<Note::WeakPtr> *    m_title_trie;
  }; // class TrieController
} // namespace gnote
// Sun Sep 30 11:31:49 PDT 2012
