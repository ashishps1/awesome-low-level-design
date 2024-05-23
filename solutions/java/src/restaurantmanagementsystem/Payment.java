package restaurantmanagementsystem;

public class Payment {
    private int id;
    private double amount;
    private PaymentMethod method;
    private PaymentStatus status;

    public Payment(int id, double amount, PaymentMethod method, PaymentStatus status) {
        this.id = id;
        this.amount = amount;
        this.method = method;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public double getAmount() {
        return amount;
    }

    public PaymentMethod getMethod() {
        return method;
    }

    public PaymentStatus getStatus() {
        return status;
    }
}
