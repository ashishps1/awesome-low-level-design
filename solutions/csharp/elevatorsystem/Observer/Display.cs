class Display : IElevatorObserver
{
    public void Update(Elevator elevator)
    {
        Console.WriteLine($"[DISPLAY] Elevator {elevator.GetId()} | Current Floor: {elevator.GetCurrentFloor()} | Direction: {elevator.GetDirection()}");
    }
}