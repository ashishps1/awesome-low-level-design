package splitwise.splittype;

import splitwise.User;

public class EqualSplit extends Split {
    public EqualSplit(User user) {
        super(user);
    }

    @Override
    public double getAmount() {
        return amount;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }
}
