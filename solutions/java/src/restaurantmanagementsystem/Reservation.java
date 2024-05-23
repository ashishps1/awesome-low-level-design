package restaurantmanagementsystem;

import java.sql.Timestamp;

public class Reservation {
    private int id;
    private String customerName;
    private String contactNumber;
    private int partySize;
    private Timestamp reservationTime;

    public Reservation(int id, String customerName, String contactNumber, int partySize, Timestamp reservationTime) {
        this.id = id;
        this.customerName = customerName;
        this.contactNumber = contactNumber;
        this.partySize = partySize;
        this.reservationTime = reservationTime;
    }
}
