public class TextEditorNaive {
    private String content = "";

    public void type(String newText) {
        content += newText;
    }

    public void undo(String previousContent) {
        content = previousContent;
    }

    public String getContent() {
        return content;
    }    
}
