package parkinglot;

import parkinglot.fee.FeeStrategy;
import parkinglot.fee.FlatRateFeeStrategy;
import parkinglot.vehicletype.Vehicle;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ParkingLot {
    private static ParkingLot instance;
    private final List<ParkingFloor> floors;
    private final Map<String, Ticket> activeTickets = new ConcurrentHashMap<>();
    private FeeStrategy feeStrategy;

    private ParkingLot() {
        floors = new ArrayList<>();
        feeStrategy = new FlatRateFeeStrategy();
    }

    public static synchronized ParkingLot getInstance() {
        if (instance == null) {
            instance = new ParkingLot();
        }
        return instance;
    }

    public void addFloor(ParkingFloor floor) {
        floors.add(floor);
    }

    public void setFeeStrategy (FeeStrategy feeStrategy) {
        this.feeStrategy = feeStrategy;
    }


    public Ticket parkVehicle(Vehicle vehicle) throws Exception {
        /**
         * For a parking lot floors will not change dynamically.
         */
        for (ParkingFloor floor : floors) {
            /**
             * Spot is thread Safe. Client need not do locking.
             */
            Optional<ParkingSpot> spotOpt = floor.getAvailableSpot(vehicle.getType());
            if (spotOpt.isPresent()) {
                ParkingSpot spot = spotOpt.get();
                /**
                 * Spot is thread safe. hence spot.park will be as well.
                 */
                if (spot.park(vehicle)) {
                    String ticketId = UUID.randomUUID().toString();
                    Ticket ticket = new Ticket(ticketId, vehicle, spot);
                    activeTickets.put(ticketId, ticket);
                    return ticket;
                }
            }
        }
        throw new Exception("No available spot for " + vehicle.getType());
    }

    public double unparkVehicle(String ticketId) throws Exception {
        Ticket ticket = activeTickets.remove(ticketId);
        if (ticket == null) throw new Exception("Invalid ticket");

        ParkingSpot spot = ticket.getSpot();
        spot.unpark();

        ticket.setExitTimestamp();
        return feeStrategy.calculateFee(ticket);
    }

    public List<ParkingFloor> getParkingFloors() {
        return floors;
    }
}
