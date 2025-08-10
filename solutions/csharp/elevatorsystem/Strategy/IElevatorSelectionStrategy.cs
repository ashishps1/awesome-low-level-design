interface IElevatorSelectionStrategy
{
    Elevator SelectElevator(List<Elevator> elevators, Request request);
}