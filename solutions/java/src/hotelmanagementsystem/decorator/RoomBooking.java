package hotelmanagementsystem.decorator;

import hotelmanagementsystem.model.Room;

public class RoomBooking implements Bookable {
    private final Room room;

    public RoomBooking(Room room) {
        this.room = room;
    }

    @Override
    public double getCost() {
        return room.getPrice();
    }

    @Override
    public String getDescription() {
        return room.getStyle() + " " + room.getType() + " Room";
    }
}
