class IdleState : IElevatorState
{
    public void Move(Elevator elevator)
    {
        if (elevator.GetUpRequests().Count > 0)
        {
            elevator.SetState(new MovingUpState());
        }
        else if (elevator.GetDownRequests().Count > 0)
        {
            elevator.SetState(new MovingDownState());
        }
        // Else stay idle
    }

    public void AddRequest(Elevator elevator, Request request)
    {
        if (request.GetTargetFloor() > elevator.GetCurrentFloor())
        {
            elevator.GetUpRequests().Add(request.GetTargetFloor());
        }
        else if (request.GetTargetFloor() < elevator.GetCurrentFloor())
        {
            elevator.GetDownRequests().Add(request.GetTargetFloor());
        }
        // If request is for current floor, doors would open (handled implicitly by moving to that floor)
    }

    public Direction GetDirection() => Direction.IDLE;
}