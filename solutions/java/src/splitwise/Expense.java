package splitwise;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;

public class Expense {
    private final String expenseId;
    private final double amount;
    private final String description;
    private final Group group;
    private final User paidBy;
    private final List<Split> splits;
    private final Date createdAt;

    public Expense(double amount, String description, User paidBy) {
        this.expenseId = UUID.randomUUID().toString();
        this.amount = amount;
        this.description = description;
        this.paidBy = paidBy;
        this.group = null;
        this.splits = new ArrayList<>();
        this.createdAt = new Date();
    }

    private Expense(Builder builder) {
        this.expenseId = UUID.randomUUID().toString();
        this.amount = builder.amount;
        this.description = builder.description;
        this.paidBy = builder.paidBy;
        this.group = builder.group;
        this.splits = builder.splits;
        this.createdAt = new Date();
    }

    public String getExpenseId() {
        return expenseId;
    }

    public double getAmount() {
        return amount;
    }

    public Date getCreatedAt() {
        return createdAt;
    }

    public Group getGroup() {
        return group;
    }

    public String getDescription() {
        return description;
    }

    public User getPaidBy() {
        return paidBy;
    }

    public List<Split> getSplits() {
        return splits;
    }

    public static class Builder {
        private double amount;
        private String description;
        private User paidBy;
        private Group group = null;
        private final List<Split> splits = new ArrayList<>();

        public Builder amount(double amount) {
            this.amount = amount;
            return this;
        }

        public Builder description(String description) {
            this.description = description;
            return this;
        }

        public Builder paidBy(User paidBy) {
            this.paidBy = paidBy;
            return this;
        }

        public Builder group(Group group) {
            this.group = group;
            return this;
        }

        public Builder addSplits(List<Split> splits) {
            this.splits.addAll(splits);
            return this;
        }

        public Expense build() {
            // Optional validations can go here
            if (amount <= 0 || paidBy == null || splits.isEmpty()) {
                throw new IllegalArgumentException("Invalid expense data");
            }
            return new Expense(this);
        }
    }
}

