package elevatorsystem.strategy;

import elevatorsystem.Elevator;
import elevatorsystem.enums.Direction;
import elevatorsystem.models.Request;

import java.util.List;
import java.util.Optional;

public class NearestElevatorStrategy implements ElevatorSelectionStrategy {
    @Override
    public Optional<Elevator> selectElevator(List<Elevator> elevators, Request request) {
        Elevator bestElevator = null;
        int minDistance = Integer.MAX_VALUE;

        for (Elevator elevator : elevators) {
            if (isSuitable(elevator, request)) {
                int distance = Math.abs(elevator.getCurrentFloor() - request.getTargetFloor());
                if (distance < minDistance) {
                    minDistance = distance;
                    bestElevator = elevator;
                }
            }
        }
        return Optional.ofNullable(bestElevator);
    }

    private boolean isSuitable(Elevator elevator, Request request) {
        if (elevator.getDirection() == Direction.IDLE)
            return true;
        if (elevator.getDirection() == request.getDirection()) {
            if (request.getDirection() == Direction.UP && elevator.getCurrentFloor() <= request.getTargetFloor())
                return true;
            if (request.getDirection() == Direction.DOWN && elevator.getCurrentFloor() >= request.getTargetFloor())
                return true;
        }
        return false;
    }
}
