package movieticketbookingsystem.entities;

import movieticketbookingsystem.enums.SeatStatus;
import movieticketbookingsystem.enums.SeatType;

public class Seat {
    private final String id;
    private final int row;
    private final int col;
    private final SeatType type;
    private SeatStatus status;

    public Seat(String id, int row, int col, SeatType type) {
        this.id = id;
        this.row = row;
        this.col = col;
        this.type = type;
        this.status = SeatStatus.AVAILABLE;
    }

    // Getters and a setter for status
    public String getId() { return id; }
    public int getRow() { return row; }
    public int getCol() { return col; }
    public SeatType getType() { return type; }
    public SeatStatus getStatus() { return status; }
    public void setStatus(SeatStatus status) { this.status = status; }
}