package airlinemanagementsystem.seat;

public class Seat {
    private final String seatNumber;
    private final SeatType type;
    private SeatStatus status;

    public Seat(String seatNumber, SeatType type) {
        this.seatNumber = seatNumber;
        this.type = type;
        this.status = SeatStatus.AVAILABLE;
    }

    public void reserve() {
        status = SeatStatus.RESERVED;
    }

    public void release() {
        status = SeatStatus.AVAILABLE;
    }
}
