package splitwise;

import java.util.Date;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.stream.Collectors;

public class Group {
    private final String groupId;
    private final String name;
    private final List<User> members;
    private final List<Expense> expenses;
    private final Date createdAt;

    public Group(String name, List<User> members) {
        this.groupId = UUID.randomUUID().toString();
        this.name = name;
        this.members = members;
        this.expenses = new CopyOnWriteArrayList<>();
        this.createdAt = new Date();
    }

    public String getGroupId() {
        return groupId;
    }

    public String getName() {
        return name;
    }

    public List<User> getMembers() {
        return members;
    }

    public List<String> getMemberIds() {
        return members.stream()
                .map(User::getUserId)
                .collect(Collectors.toList());
    }
}
