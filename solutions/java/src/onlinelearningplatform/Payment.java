package onlinelearningplatform;

import java.util.Date;

class Payment {
    private String paymentId;
    private String userId;
    private double amount;
    private String paymentMethod;
    private Date paymentDate;

    public Payment(String paymentId, String userId, double amount, String paymentMethod, Date paymentDate) {
        this.paymentId = paymentId;
        this.userId = userId;
        this.amount = amount;
        this.paymentMethod = paymentMethod;
        this.paymentDate = paymentDate;
    }
}