public class TextEditorUndoV1 {
    public static void main(String[] args) {
        TextEditorNaive editor = new TextEditorNaive();

        editor.type("Hello");
        String snapshot1 = editor.getContent(); // manual snapshot

        editor.type(" World");
        String snapshot2 = editor.getContent();

        System.out.println("Current Content: " + editor.getContent()); // Hello World

        // Undo 1 step
        editor.undo(snapshot1);
        System.out.println("After Undo: " + editor.getContent()); // Hello
    }
}