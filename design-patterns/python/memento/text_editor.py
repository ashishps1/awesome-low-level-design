from .text_editor_memento import TextEditorMemento

class TextEditor:
    def __init__(self):
        self.content = ""

    def type(self, new_text: str) -> None:
        self.content += new_text
        print(f"Typed: {new_text}")

    def get_content(self) -> str:
        return self.content

    def save(self) -> TextEditorMemento:
        print(f'Saving state: "{self.content}"')
        return TextEditorMemento(self.content)

    def restore(self, memento: TextEditorMemento) -> None:
        self.content = memento.state
        print(f'Restored state to: "{self.content}"') 