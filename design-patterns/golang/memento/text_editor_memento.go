package memento

// TextEditorMemento stores the state of the TextEditor
type TextEditorMemento struct {
	State string
}

// NewTextEditorMemento creates a new memento with the given state
func NewTextEditorMemento(state string) *TextEditorMemento {
	return &TextEditorMemento{State: state}
}
