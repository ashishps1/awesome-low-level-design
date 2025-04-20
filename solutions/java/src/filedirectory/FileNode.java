package filedirectory;

// File Node with metadata
public class FileNode extends AbstractNode {
    private String content;
    private int size;

    public FileNode(String name) {
        super(name);
        this.content = "";
        this.size = 0;
    }

    public void appendContent(String newContent) {
        this.content += newContent;
        this.size += newContent.length();
    }

    public String readContent() {
        return content;
    }

    public int getSize() {
        return size;
    }
}