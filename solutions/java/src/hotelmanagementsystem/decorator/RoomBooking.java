package hotelmanagementsystem.decorator;

import hotelmanagementsystem.model.Room;

public class RoomBooking implements Bookable {
    private final Room room;
    private final int numberOfNights;

    public RoomBooking(Room room, int numberOfNights) {
        this.room = room;
        this.numberOfNights = numberOfNights;
    }

    @Override
    public double getCost() {
        return room.getPrice() * numberOfNights;
    }

    @Override
    public String getDescription() {
        return room.getStyle() + " " + room.getType() + " Room";
    }
}
