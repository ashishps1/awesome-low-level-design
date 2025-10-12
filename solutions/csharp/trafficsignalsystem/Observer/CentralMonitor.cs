class CentralMonitor : ITrafficObserver
{
    public void Update(int intersectionId, Direction direction, LightColor color)
    {
        Console.WriteLine($"[MONITOR] Intersection {intersectionId}: Light for {direction} direction changed to {color}.");
    }
}