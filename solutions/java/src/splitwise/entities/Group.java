package splitwise.entities;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Group {
    private final String id;
    private final String name;
    private final List<User> members;

    public Group(String name, List<User> members) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.members = members;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<User> getMembers() {
        return new ArrayList<>(members);
    }
}
