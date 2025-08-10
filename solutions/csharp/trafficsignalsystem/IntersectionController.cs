class IntersectionController
{
    private readonly int id;
    private readonly Dictionary<Direction, TrafficLight> trafficLights;
    private IIntersectionState currentState;
    private readonly long greenDuration;
    private readonly long yellowDuration;
    private volatile bool running = true;

    public IntersectionController(int id, Dictionary<Direction, TrafficLight> trafficLights, 
                                  long greenDuration, long yellowDuration)
    {
        this.id = id;
        this.trafficLights = trafficLights;
        this.greenDuration = greenDuration;
        this.yellowDuration = yellowDuration;
        this.currentState = new NorthSouthGreenState(); // Initial state for the intersection
    }

    public int GetId() => id;
    public long GetGreenDuration() => greenDuration;
    public long GetYellowDuration() => yellowDuration;
    public TrafficLight GetLight(Direction direction) => trafficLights[direction];

    public void SetState(IIntersectionState state)
    {
        this.currentState = state;
    }

    public void Start()
    {
        Task.Run(() => Run());
    }

    public void Stop()
    {
        this.running = false;
    }

    public void Run()
    {
        while (running)
        {
            try
            {
                currentState.Handle(this);
            }
            catch (Exception e)
            {
                Console.WriteLine($"Intersection {id} encountered an error: {e.Message}");
                running = false;
            }
        }
    }
}

// Builder Pattern
class IntersectionControllerBuilder
{
    private readonly int id;
    private long greenDuration = 5000; // default 5s
    private long yellowDuration = 2000; // default 2s
    private readonly List<ITrafficObserver> observers = new List<ITrafficObserver>();

    public IntersectionControllerBuilder(int id)
    {
        this.id = id;
    }

    public IntersectionControllerBuilder WithDurations(long green, long yellow)
    {
        this.greenDuration = green;
        this.yellowDuration = yellow;
        return this;
    }

    public IntersectionControllerBuilder AddObserver(ITrafficObserver observer)
    {
        this.observers.Add(observer);
        return this;
    }

    public IntersectionController Build()
    {
        var lights = new Dictionary<Direction, TrafficLight>();
        foreach (Direction dir in Enum.GetValues(typeof(Direction)).Cast<Direction>())
        {
            TrafficLight light = new TrafficLight(id, dir);
            // Attach all registered observers to each light
            foreach (var observer in observers)
            {
                light.AddObserver(observer);
            }
            lights[dir] = light;
        }
        return new IntersectionController(id, lights, greenDuration, yellowDuration);
    }
}