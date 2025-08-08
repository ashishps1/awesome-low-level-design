package hotelmanagementsystem.state;

import hotelmanagementsystem.model.Room;

public class MaintenanceState implements RoomState {
    @Override
    public void book(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is under maintenance.");
    }

    @Override
    public void checkIn(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is under maintenance.");
    }

    @Override
    public void checkOut(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is under maintenance.");
    }

    @Override
    public void markForMaintenance(Room room) {
        System.out.println("Room " + room.getRoomNumber() + " is already under maintenance. Marking it as available now.");
        room.setState(new AvailableState());
    }
}
