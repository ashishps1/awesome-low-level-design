package filedirectory.strategy;


import filedirectory.AbstractNode;
import filedirectory.DirectoryNode;

import java.util.*;

public // Search strategy interface
interface NodeSearchStrategy {
    List<AbstractNode> search(DirectoryNode directory, Map<String, Object> params);
}
