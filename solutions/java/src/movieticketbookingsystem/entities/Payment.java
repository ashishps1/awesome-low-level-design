package movieticketbookingsystem.entities;

import movieticketbookingsystem.enums.PaymentStatus;

import java.util.UUID;

public class Payment {
    private final String id;
    private final double amount;
    private final PaymentStatus status;
    private final String transactionId;

    public Payment(double amount, PaymentStatus status, String transactionId) {
        this.id = UUID.randomUUID().toString();
        this.amount = amount;
        this.status = status;
        this.transactionId = transactionId;
    }

    public PaymentStatus getStatus() { return status; }
}
