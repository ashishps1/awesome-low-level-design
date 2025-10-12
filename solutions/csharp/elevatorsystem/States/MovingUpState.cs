class MovingUpState : IElevatorState
{
    public void Move(Elevator elevator)
    {
        if (elevator.GetUpRequests().Count == 0)
        {
            elevator.SetState(new IdleState());
            return;
        }

        int nextFloor = elevator.GetUpRequests().Min();
        elevator.SetCurrentFloor(elevator.GetCurrentFloor() + 1);

        if (elevator.GetCurrentFloor() == nextFloor)
        {
            Console.WriteLine($"Elevator {elevator.GetId()} stopped at floor {nextFloor}");
            elevator.GetUpRequests().Remove(nextFloor);
        }

        if (elevator.GetUpRequests().Count == 0)
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
        if (request.GetDirection() == Direction.UP && request.GetTargetFloor() >= elevator.GetCurrentFloor())
        {
            elevator.GetUpRequests().Add(request.GetTargetFloor());
        }
        else if (request.GetDirection() == Direction.DOWN)
        {
            elevator.GetDownRequests().Add(request.GetTargetFloor());
        }
    }

    public Direction GetDirection() => Direction.UP;
}