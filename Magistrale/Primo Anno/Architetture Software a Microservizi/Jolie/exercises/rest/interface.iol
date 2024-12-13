type Note { id: int note: string }
type CreateNoteRequest { note: string }
type ListNotesRequest { }
type ListNotesResponse { notes*: Note }
type DeleteNoteRequest { id: int }

interface NotesInterface {
RequestResponse:
    createNote( CreateNoteRequest )( Note ),
    listNotes( ListNotesRequest )( ListNotesResponse ),
    deleteNote( DeleteNoteRequest )( void ) throws NoteNotFound( string )
}