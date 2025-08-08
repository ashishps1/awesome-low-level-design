package hotelmanagementsystem.specification;

import hotelmanagementsystem.enums.RoomType;
import hotelmanagementsystem.model.Room;

public class RoomTypeSpecification extends AbstractSpecification<Room> {
    private final RoomType type;

    public RoomTypeSpecification(RoomType type) {
        this.type = type;
    }

    @Override
    public boolean isSatisfiedBy(Room item) {
        return item.getType() == type;
    }
}
