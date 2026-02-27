package hotelmanagementsystem.specification;

import hotelmanagementsystem.enums.RoomStyle;
import hotelmanagementsystem.model.Room;

public class RoomStyleSpecification implements Specification<Room> {
    private final RoomStyle style;

    public RoomStyleSpecification(RoomStyle style) {
        this.style = style;
    }

    @Override
    public boolean isSatisfiedBy(Room item) {
        return item.getStyle() == style;
    }
}
