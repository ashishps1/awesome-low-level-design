class YellowState : ISignalState
{
    public void Handle(TrafficLight context)
    {
        context.SetColor(LightColor.YELLOW);
        // After being yellow, the next state is red.
        context.SetNextState(new RedState());
    }
}