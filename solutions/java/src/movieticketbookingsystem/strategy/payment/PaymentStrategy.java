package movieticketbookingsystem.strategy.payment;

import movieticketbookingsystem.entities.Payment;

public interface PaymentStrategy {
    Payment pay(double amount);
}
