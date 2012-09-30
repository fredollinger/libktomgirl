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
