package hotelmanagementsystem.state;

import hotelmanagementsystem.model.Room;

public class OccupiedState implements RoomState {
    @Override
    public void book(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is already occupied.");
    }

    @Override
    public void checkIn(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is already checked in.");
    }

    @Override
    public void checkOut(Room room) {
        System.out.println("Checking out of room " + room.getRoomNumber() + ".");
        room.setState(new AvailableState());
    }

    @Override
    public void markForMaintenance(Room room) {
        System.out.println("Error: Cannot mark an occupied room for maintenance. Please check out first.");
    }
}
