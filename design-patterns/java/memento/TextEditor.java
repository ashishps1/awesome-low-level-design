public class TextEditor {
    private String content = "";

    public void type(String newText) {
        content += newText;
        System.out.println("Typed: " + newText);
    }

    public String getContent() {
        return content;
    }

    public TextEditorMemento save() {
        System.out.println("Saving state: \"" + content + "\"");
        return new TextEditorMemento(content);
    }

    public void restore(TextEditorMemento memento) {
        content = memento.getState();
        System.out.println("Restored state to: \"" + content + "\"");
    }
}