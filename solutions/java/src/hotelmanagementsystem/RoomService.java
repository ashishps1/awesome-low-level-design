package hotelmanagementsystem;

import hotelmanagementsystem.model.Room;
import hotelmanagementsystem.specification.Specification;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class RoomService {
    private final List<Room> rooms = new ArrayList<>();

    public void addRoom(Room room) {
        rooms.add(room);
    }

    public List<Room> findRooms(Specification<Room> spec) {
        return rooms.stream()
                .filter(spec::isSatisfiedBy)
                .collect(Collectors.toList());
    }

    public Room findRoomByNumber(String roomNumber) {
        return rooms.stream()
                .filter(r -> r.getRoomNumber().equals(roomNumber))
                .findFirst()
                .orElse(null);
    }
}
