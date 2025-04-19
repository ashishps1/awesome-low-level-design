package parkinglot;

import java.time.LocalDateTime;
import java.util.concurrent.atomic.AtomicInteger;

import parkinglot.vehicletype.Vehicle;

public class Ticket {
    int ticketId;
    Vehicle vehicle;
    int parkingLotId;
    int level;
    LocalDateTime entryTime;

    public Ticket(Vehicle vehicle, int parkingLotId, int level, LocalDateTime entryTime) {
        this.vehicle = vehicle;
        this.parkingLotId = parkingLotId;
        this.level = level;
        this.entryTime = entryTime;
    }

    public Ticket(AtomicInteger ticketId, Ticket ticket) {
        this.ticketId = Integer.parseInt(ticketId.toString());
        this.vehicle = ticket.getVehicle();
        this.parkingLotId = ticket.getParkingLotId();
        this.level = ticket.getLevel();
        this.entryTime = ticket.getEntryTime();
    }
    private LocalDateTime getEntryTime() {
        return  entryTime;
    }

    private int getLevel() {
        return level;
    }

    private int getParkingLotId() {
        return parkingLotId;
    }

    public int getTicketId() {
        return ticketId;
    }
    public Vehicle getVehicle() {
        return vehicle;
    }
}

