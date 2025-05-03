package parkinglot.fee;

import parkinglot.Ticket;

public class FlatRateFeeStrategy implements FeeStrategy {

    private static final double RATE_PER_HOUR = 10.0;

    @Override
    public double calculateFee(Ticket ticket) {
        long duration = ticket.getExitTimestamp() - ticket.getEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * RATE_PER_HOUR;
    }
}