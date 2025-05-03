package parkinglot.fee;

import parkinglot.Ticket;

public interface FeeStrategy {
    double calculateFee(Ticket ticket);
}
