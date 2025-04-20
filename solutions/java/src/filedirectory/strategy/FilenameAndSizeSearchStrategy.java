package filedirectory.strategy;

import filedirectory.*;
import filedirectory.chainofresponsibility.FileSizeFilter;
import filedirectory.chainofresponsibility.FilenameFilter;
import filedirectory.chainofresponsibility.NodeFilterChain;

import java.util.*;

public class FilenameAndSizeSearchStrategy implements NodeSearchStrategy {
    private NodeFilterChain filterChain;

    public FilenameAndSizeSearchStrategy() {
        this.filterChain = new NodeFilterChain();
        filterChain.addFilter(new FilenameFilter());
        filterChain.addFilter(new FileSizeFilter());
    }

    @Override
    public List<AbstractNode> search(DirectoryNode directory, Map<String, Object> params) {
        List<AbstractNode> result = new ArrayList<>();
        searchRecursive(directory, params, result);
        return result;
    }

    private void searchRecursive(DirectoryNode dir, Map<String, Object> params, List<AbstractNode> result) {
        for (AbstractNode node : dir.getChildren()) {
            if (filterChain.applyFilters(node, params)) {
                result.add(node);
            }
            if (node instanceof DirectoryNode) {
                searchRecursive((DirectoryNode) node, params, result);
            }
        }
    }
}
