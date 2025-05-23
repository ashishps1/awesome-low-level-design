from typing import List
from .text_editor import TextEditor
from .text_editor_memento import TextEditorMemento

class TextEditorUndoManager:
    def __init__(self):
        self.history: List[TextEditorMemento] = []

    def save(self, editor: TextEditor) -> None:
        self.history.append(editor.save())

    def undo(self, editor: TextEditor) -> None:
        if self.history:
            editor.restore(self.history.pop())
        else:
            print("Nothing to undo.") 