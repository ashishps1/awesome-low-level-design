class MovingDownState : IElevatorState
{
    public void Move(Elevator elevator)
    {
        if (elevator.GetDownRequests().Count == 0)
        {
            elevator.SetState(new IdleState());
            return;
        }

        int nextFloor = elevator.GetDownRequests().Max();
        elevator.SetCurrentFloor(elevator.GetCurrentFloor() - 1);

        if (elevator.GetCurrentFloor() == nextFloor)
        {
            Console.WriteLine($"Elevator {elevator.GetId()} stopped at floor {nextFloor}");
            elevator.GetDownRequests().Remove(nextFloor);
        }

        if (elevator.GetDownRequests().Count == 0)
        {
            elevator.SetState(new IdleState());
        }
    }

    public void AddRequest(Elevator elevator, Request request)
    {
        // Internal requests always get added to the appropriate queue
        if (request.GetSource() == RequestSource.INTERNAL)
        {
            if (request.GetTargetFloor() > elevator.GetCurrentFloor())
            {
                elevator.GetUpRequests().Add(request.GetTargetFloor());
            }
            else
            {
                elevator.GetDownRequests().Add(request.GetTargetFloor());
            }
            return;
        }

        // External requests
        if (request.GetDirection() == Direction.DOWN && request.GetTargetFloor() <= elevator.GetCurrentFloor())
        {
            elevator.GetDownRequests().Add(request.GetTargetFloor());
        }
        else if (request.GetDirection() == Direction.UP)
        {
            elevator.GetUpRequests().Add(request.GetTargetFloor());
        }
    }

    public Direction GetDirection() => Direction.DOWN;
}