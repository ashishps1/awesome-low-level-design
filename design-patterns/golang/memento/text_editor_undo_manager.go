package memento

import "fmt"

// TextEditorUndoManager manages the undo stack for the TextEditor
type TextEditorUndoManager struct {
	history []*TextEditorMemento
}

// NewTextEditorUndoManager creates a new undo manager
func NewTextEditorUndoManager() *TextEditorUndoManager {
	return &TextEditorUndoManager{history: make([]*TextEditorMemento, 0)}
}

// Save saves the current state of the editor
func (m *TextEditorUndoManager) Save(editor *TextEditor) {
	m.history = append(m.history, editor.Save())
}

// Undo restores the last saved state
func (m *TextEditorUndoManager) Undo(editor *TextEditor) {
	n := len(m.history)
	if n == 0 {
		fmt.Println("Nothing to undo.")
		return
	}
	last := m.history[n-1]
	m.history = m.history[:n-1]
	editor.Restore(last)
}
