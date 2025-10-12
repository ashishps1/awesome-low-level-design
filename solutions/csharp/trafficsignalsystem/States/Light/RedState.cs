class RedState : ISignalState
{
    public void Handle(TrafficLight context)
    {
        context.SetColor(LightColor.RED);
        // Red is a stable state, it transitions to green only when the intersection controller commands it.
        // So, the next state is self.
        context.SetNextState(new RedState());
    }
}