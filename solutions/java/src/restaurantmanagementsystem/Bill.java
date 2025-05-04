package restaurantmanagementsystem;

import restaurantmanagementsystem.payment.PaymentStatus;

public class Bill {
    private final String orderId;
    private final double totalAmount;
    private PaymentStatus paymentStatus;

    public Bill(String orderId, double totalAmount) {
        this.orderId = orderId;
        this.totalAmount = totalAmount;
        this.paymentStatus = PaymentStatus.PENDING;
    }

    public void markPaymentCompleted() {
        this.paymentStatus = PaymentStatus.COMPLETED;
    }

    public void markPaymentFailed() {
        this.paymentStatus = PaymentStatus.FAILED;
    }

    public double getTotalAmount() {
        return totalAmount;
    }

    public String getOrderId() {
        return orderId;
    }
}
