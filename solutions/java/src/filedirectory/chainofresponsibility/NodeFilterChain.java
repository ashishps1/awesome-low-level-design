package filedirectory.chainofresponsibility;

import filedirectory.AbstractNode;

import java.util.*;

// Chain of Responsibility: Combines multiple filters
public class NodeFilterChain {
    private List<NodeFilter> filters;

    public NodeFilterChain() {
        this.filters = new ArrayList<>();
    }

    public void addFilter(NodeFilter filter) {
        filters.add(filter);
    }

    public boolean applyFilters(AbstractNode node, Map<String, Object> params) {
        for (NodeFilter filter : filters) {
            if (!filter.apply(node, params)) {
                return false; // If any filter fails, reject the node
            }
        }
        return true;
    }
}