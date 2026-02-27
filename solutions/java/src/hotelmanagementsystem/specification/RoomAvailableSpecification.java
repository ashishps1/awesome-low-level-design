package hotelmanagementsystem.specification;

import hotelmanagementsystem.model.Room;
import hotelmanagementsystem.state.AvailableState;

public class RoomAvailableSpecification implements Specification<Room> {
    @Override
    public boolean isSatisfiedBy(Room item) {
        return item.getState() instanceof AvailableState;
    }
}
