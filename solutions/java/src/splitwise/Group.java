package splitwise;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class Group {
    private final String id;
    private final String name;
    private final List<User> members;
    private final List<Expense> expenses;

    public Group(String id, String name) {
        this.id = id;
        this.name = name;
        this.members = new CopyOnWriteArrayList<>();
        this.expenses = new CopyOnWriteArrayList<>();
    }

    public void addMember(User user) {
        members.add(user);
    }

    public void addExpense(Expense expense) {
        expenses.add(expense);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<User> getMembers() {
        return members;
    }

    public List<Expense> getExpenses() {
        return expenses;
    }
}
