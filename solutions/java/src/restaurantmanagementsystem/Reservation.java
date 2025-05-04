package restaurantmanagementsystem;

import java.sql.Timestamp;
import java.util.UUID;

public class Reservation {
    private final String id;
    private final String customerName;
    private final String contactNumber;
    private final int partySize;
    private final Timestamp reservationTime;

    public Reservation(String customerName, String contactNumber, int partySize, Timestamp reservationTime) {
        this.id = UUID.randomUUID().toString();
        this.customerName = customerName;
        this.contactNumber = contactNumber;
        this.partySize = partySize;
        this.reservationTime = reservationTime;
    }
}
