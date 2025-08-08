package elevatorsystem.state;

import elevatorsystem.Elevator;
import elevatorsystem.enums.Direction;
import elevatorsystem.models.Request;

public interface ElevatorState {
    void move(Elevator elevator);
    void addRequest(Elevator elevator, Request request);
    Direction getDirection();
}
