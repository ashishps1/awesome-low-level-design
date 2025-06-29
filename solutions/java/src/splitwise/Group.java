package splitwise;

import java.util.Date;
import java.util.List;
import java.util.UUID;

public class Group {
    private final String groupId;
    private final String name;
    private final List<User> members;
    private final Date createdAt;

    public Group(String name, List<User> members) {
        this.groupId = UUID.randomUUID().toString();
        this.name = name;
        this.members = members;
        this.createdAt = new Date();
    }

    public String getGroupId() {
        return groupId;
    }

    public String getName() {
        return name;
    }
}
