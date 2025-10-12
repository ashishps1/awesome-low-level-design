class NorthSouthGreenState : IIntersectionState
{
    public void Handle(IntersectionController context)
    {
        Console.WriteLine($"\n--- INTERSECTION {context.GetId()}: Cycle Start -> North-South GREEN ---");

        // Turn North and South green, ensure East and West are red
        context.GetLight(Direction.NORTH).StartGreen();
        context.GetLight(Direction.SOUTH).StartGreen();
        context.GetLight(Direction.EAST).SetColor(LightColor.RED);
        context.GetLight(Direction.WEST).SetColor(LightColor.RED);

        // Wait for green light duration
        Thread.Sleep((int)context.GetGreenDuration());

        // Transition North and South to Yellow
        context.GetLight(Direction.NORTH).Transition();
        context.GetLight(Direction.SOUTH).Transition();

        // Wait for yellow light duration
        Thread.Sleep((int)context.GetYellowDuration());

        // Transition North and South to Red
        context.GetLight(Direction.NORTH).Transition();
        context.GetLight(Direction.SOUTH).Transition();

        // Change the intersection's state to let East-West go
        context.SetState(new EastWestGreenState());
    }
}