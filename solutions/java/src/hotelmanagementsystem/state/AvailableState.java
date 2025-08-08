package hotelmanagementsystem.state;

import hotelmanagementsystem.model.Room;

public class AvailableState implements RoomState {
    @Override
    public void book(Room room) {
        System.out.println("Booking room " + room.getRoomNumber() + ".");
        room.setState(new OccupiedState());
    }

    @Override
    public void checkIn(Room room) {
        System.out.println("Checking into room " + room.getRoomNumber() + ".");
        room.setState(new OccupiedState());
    }

    @Override
    public void checkOut(Room room) {
        System.out.println("Error: Room " + room.getRoomNumber() + " is not occupied.");
    }

    @Override
    public void markForMaintenance(Room room) {
        System.out.println("Marking room " + room.getRoomNumber() + " for maintenance.");
        room.setState(new MaintenanceState());
    }
}
