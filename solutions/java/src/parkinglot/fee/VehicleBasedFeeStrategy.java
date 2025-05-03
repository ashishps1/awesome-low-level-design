package parkinglot.fee;

import parkinglot.Ticket;
import parkinglot.vehicletype.VehicleType;

import java.util.Map;

public class VehicleBasedFeeStrategy implements FeeStrategy {
    private final Map<VehicleType, Double> hourlyRates = Map.of(
            VehicleType.CAR, 20.0,
            VehicleType.BIKE, 10.0,
            VehicleType.TRUCK, 30.0
    );

    @Override
    public double calculateFee(Ticket ticket) {
        long duration = ticket.getExitTimestamp() - ticket.getEntryTimestamp();
        long hours = (duration / (1000 * 60 * 60)) + 1;
        return hours * hourlyRates.get(ticket.getVehicle().getType());
    }
}