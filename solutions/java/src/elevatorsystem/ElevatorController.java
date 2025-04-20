package elevatorsystem;

import java.util.ArrayList;
import java.util.List;

public class ElevatorController {
    private final List<Elevator> elevators;

    public ElevatorController(int numElevators, int capacity) {
        elevators = new ArrayList<>();
        for (int i = 0; i < numElevators; i++) {
            Elevator elevator = new Elevator(i + 1, capacity);
            elevators.add(elevator);
            new Thread(elevator::run).start();
        }
    }

    public void requestElevator(int sourceFloor, int destinationFloor) {
        Elevator optimalElevator = findOptimalElevator(sourceFloor, destinationFloor);
        optimalElevator.addRequest(new Request(sourceFloor, destinationFloor));
    }

    private Elevator findOptimalElevator(int sourceFloor, int destinationFloor) {
        Elevator optimalElevator = null;
        int minDistance = Integer.MAX_VALUE;
        //first preference to direction.
        Direction userDirection = (sourceFloor - destinationFloor) > 0 ? Direction.DOWN : Direction.UP;
        List<Elevator> optimalElevators = elevators.stream().filter(e -> e.getCurrentDirection()==userDirection).findAny().isPresent() ? 
             elevators.stream().filter(e -> e.getCurrentDirection()==userDirection).collect(Collectors.toList()) : elevators;
        
        for (Elevator elevator : optimalElevators) {
            int distance = Math.abs(sourceFloor - elevator.getCurrentFloor());
            if (distance < minDistance) {
                minDistance = distance;
                optimalElevator = elevator;
            }
        }

        return optimalElevator;
    }
}
