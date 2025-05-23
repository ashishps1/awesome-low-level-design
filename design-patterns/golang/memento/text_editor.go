package memento

import "fmt"

// TextEditor is the originator that can save and restore its state
type TextEditor struct {
	content string
}

// NewTextEditor creates a new TextEditor
func NewTextEditor() *TextEditor {
	return &TextEditor{}
}

// Type appends text to the editor
func (e *TextEditor) Type(words string) {
	e.content += words
	fmt.Printf("Typed: %s\n", words)
}

// GetContent returns the current content
func (e *TextEditor) GetContent() string {
	return e.content
}

// Save creates a memento of the current state
func (e *TextEditor) Save() *TextEditorMemento {
	fmt.Printf("Saved state: %s\n", e.content)
	return NewTextEditorMemento(e.content)
}

// Restore restores the state from a memento
func (e *TextEditor) Restore(memento *TextEditorMemento) {
	e.content = memento.State
	fmt.Printf("Restored state: %s\n", e.content)
}
