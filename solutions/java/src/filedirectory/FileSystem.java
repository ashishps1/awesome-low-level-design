package filedirectory;

import filedirectory.strategy.NodeSearchStrategy;

import java.util.*;

public class FileSystem {
    private DirectoryNode root;

    public FileSystem() {
        this.root = new DirectoryNode("/");
    }

    private DirectoryNode traverse(String path, boolean createMissingDirs) {
        String[] parts = path.split("/");
        DirectoryNode current = root;

        for (int i = 1; i < parts.length; i++) {
            if (!(current.getNode(parts[i]) instanceof DirectoryNode)) {
                if (createMissingDirs) {
                    current.addNode(new DirectoryNode(parts[i]));
                } else {
                    return null;
                }
            }
            current = (DirectoryNode) current.getNode(parts[i]);
        }
        return current;
    }

    public void mkdir(String path) {
        traverse(path, true);
    }

    public void addFile(String filePath, String content) {
        DirectoryNode parent = traverse(filePath.substring(0, filePath.lastIndexOf("/")), true);
        String fileName = filePath.substring(filePath.lastIndexOf("/") + 1);

        FileNode file = (FileNode) parent.getNode(fileName);
        if (file == null) {
            file = new FileNode(fileName);
            parent.addNode(file);
        }
        file.appendContent(content);
    }

    public List<AbstractNode> searchNodes(String directoryPath, NodeSearchStrategy strategy, Map<String, Object> params) {
        DirectoryNode directory = traverse(directoryPath, false);
        if (directory == null) {
            throw new IllegalArgumentException("Directory not found: " + directoryPath);
        }
        return strategy.search(directory, params);
    }
}
