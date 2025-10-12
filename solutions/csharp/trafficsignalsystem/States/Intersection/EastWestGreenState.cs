class EastWestGreenState : IIntersectionState
{
    public void Handle(IntersectionController context)
    {
        Console.WriteLine($"\n--- INTERSECTION {context.GetId()}: Cycle -> East-West GREEN ---");

        // Turn East and West green, ensure North and South are red
        context.GetLight(Direction.EAST).StartGreen();
        context.GetLight(Direction.WEST).StartGreen();
        context.GetLight(Direction.NORTH).SetColor(LightColor.RED);
        context.GetLight(Direction.SOUTH).SetColor(LightColor.RED);

        // Wait for green light duration
        Thread.Sleep((int)context.GetGreenDuration());

        // Transition East and West to Yellow
        context.GetLight(Direction.EAST).Transition();
        context.GetLight(Direction.WEST).Transition();

        // Wait for yellow light duration
        Thread.Sleep((int)context.GetYellowDuration());

        // Transition East and West to Red
        context.GetLight(Direction.EAST).Transition();
        context.GetLight(Direction.WEST).Transition();

        // Change the intersection's state back to let North-South go
        context.SetState(new NorthSouthGreenState());
    }
}