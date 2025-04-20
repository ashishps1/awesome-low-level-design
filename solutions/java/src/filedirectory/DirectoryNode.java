package filedirectory;

import java.util.*;

// Directory Node containing files and subdirectories
public class DirectoryNode extends AbstractNode {
    private Map<String, AbstractNode> children;

    public DirectoryNode(String name) {
        super(name);
        this.children = new HashMap<>();
    }

    public void addNode(AbstractNode node) {
        children.put(node.getName(), node);
    }

    public List<AbstractNode> getChildren() {
        return new ArrayList<>(children.values());
    }

    public AbstractNode getNode(String name) {
        return children.get(name);
    }
}
