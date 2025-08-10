class GreenState : ISignalState
{
    public void Handle(TrafficLight context)
    {
        context.SetColor(LightColor.GREEN);
        // After being green, the next state is yellow.
        context.SetNextState(new YellowState());
    }
}