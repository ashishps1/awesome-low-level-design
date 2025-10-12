package movieticketbookingsystem.enums;

public enum SeatType {
    REGULAR(50.0),
    PREMIUM(80.0),
    RECLINER(120.0);

    private final double price;

    SeatType(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }
}
