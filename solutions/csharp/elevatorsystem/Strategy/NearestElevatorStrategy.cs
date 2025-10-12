class NearestElevatorStrategy : IElevatorSelectionStrategy
{
    public Elevator SelectElevator(List<Elevator> elevators, Request request)
    {
        Elevator bestElevator = null;
        int minDistance = int.MaxValue;

        foreach (Elevator elevator in elevators)
        {
            if (IsSuitable(elevator, request))
            {
                int distance = Math.Abs(elevator.GetCurrentFloor() - request.GetTargetFloor());
                if (distance < minDistance)
                {
                    minDistance = distance;
                    bestElevator = elevator;
                }
            }
        }
        return bestElevator;
    }

    private bool IsSuitable(Elevator elevator, Request request)
    {
        if (elevator.GetDirection() == Direction.IDLE)
            return true;
        if (elevator.GetDirection() == request.GetDirection())
        {
            if (request.GetDirection() == Direction.UP && elevator.GetCurrentFloor() <= request.GetTargetFloor())
                return true;
            if (request.GetDirection() == Direction.DOWN && elevator.GetCurrentFloor() >= request.GetTargetFloor())
                return true;
        }
        return false;
    }
}