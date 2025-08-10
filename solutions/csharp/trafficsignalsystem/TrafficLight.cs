class TrafficLight
{
    private readonly int intersectionId;
    private readonly Direction direction;
    private LightColor currentColor;
    private ISignalState currentState;
    private ISignalState nextState;
    private readonly List<ITrafficObserver> observers = new List<ITrafficObserver>();

    public TrafficLight(int intersectionId, Direction direction)
    {
        this.intersectionId = intersectionId;
        this.direction = direction;
        this.currentState = new RedState(); // Default state is Red
        this.currentState.Handle(this);
    }

    // This is called by the IntersectionController to initiate a G-Y-R cycle
    public void StartGreen()
    {
        this.currentState = new GreenState();
        this.currentState.Handle(this);
    }

    // This is called by the IntersectionController to transition from G->Y or Y->R
    public void Transition()
    {
        this.currentState = this.nextState;
        this.currentState.Handle(this);
    }

    public void SetColor(LightColor color)
    {
        if (this.currentColor != color)
        {
            this.currentColor = color;
            NotifyObservers();
        }
    }

    public void SetNextState(ISignalState state)
    {
        this.nextState = state;
    }

    public LightColor GetCurrentColor() => currentColor;
    public Direction GetDirection() => direction;

    // Observer pattern methods
    public void AddObserver(ITrafficObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(ITrafficObserver observer)
    {
        observers.Remove(observer);
    }

    private void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.Update(intersectionId, direction, currentColor);
        }
    }
}