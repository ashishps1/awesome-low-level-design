package filedirectory;

import java.util.Date;

// Abstract class for files and directories
public abstract class AbstractNode {
    protected String name;
    protected Date createdAt;

    public AbstractNode(String name) {
        this.name = name;
        this.createdAt = new Date();
    }

    public String getName() {
        return name;
    }

    public Date getCreatedAt() {
        return createdAt;
    }
}