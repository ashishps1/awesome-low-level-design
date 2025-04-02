package filedirectory.chainofresponsibility;

import filedirectory.AbstractNode;

import java.util.Map;
import java.util.regex.Pattern;

// Concrete Filter: Filter by filename regex
public class FilenameFilter implements NodeFilter {
    @Override
    public boolean apply(AbstractNode node, Map<String, Object> params) {
        if (!params.containsKey("filenameRegex")) return true;
        String regex = (String) params.get("filenameRegex");
        return Pattern.matches(regex, node.getName());
    }
}