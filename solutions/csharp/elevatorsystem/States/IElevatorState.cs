interface IElevatorState
{
    void Move(Elevator elevator);
    void AddRequest(Elevator elevator, Request request);
    Direction GetDirection();
}