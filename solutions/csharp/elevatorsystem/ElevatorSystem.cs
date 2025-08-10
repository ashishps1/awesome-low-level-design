class ElevatorSystem
{
    private static ElevatorSystem instance;
    private static readonly object lockObject = new object();

    private readonly Dictionary<int, Elevator> elevators;
    private readonly IElevatorSelectionStrategy selectionStrategy;
    private readonly List<Task> elevatorTasks;

    private ElevatorSystem(int numElevators)
    {
        this.selectionStrategy = new NearestElevatorStrategy();
        this.elevatorTasks = new List<Task>();

        List<Elevator> elevatorList = new List<Elevator>();
        Display display = new Display(); // Create the observer

        for (int i = 1; i <= numElevators; i++)
        {
            Elevator elevator = new Elevator(i);
            elevator.AddObserver(display); // Attach the observer
            elevatorList.Add(elevator);
        }

        this.elevators = elevatorList.ToDictionary(e => e.GetId(), e => e);
    }

    public static ElevatorSystem GetInstance(int numElevators)
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new ElevatorSystem(numElevators);
                }
            }
        }
        return instance;
    }

    public void Start()
    {
        foreach (Elevator elevator in elevators.Values)
        {
            elevatorTasks.Add(Task.Run(() => elevator.Run()));
        }
    }

    // --- Facade Methods ---

    // EXTERNAL Request (Hall Call)
    public void RequestElevator(int floor, Direction direction)
    {
        Console.WriteLine($"\n>> EXTERNAL Request: User at floor {floor} wants to go {direction}");
        Request request = new Request(floor, direction, RequestSource.EXTERNAL);

        // Use strategy to find the best elevator
        Elevator selectedElevator = selectionStrategy.SelectElevator(elevators.Values.ToList(), request);

        if (selectedElevator != null)
        {
            selectedElevator.AddRequest(request);
        }
        else
        {
            Console.WriteLine("System busy, please wait.");
        }
    }

    // INTERNAL Request (Cabin Call)
    public void SelectFloor(int elevatorId, int destinationFloor)
    {
        Console.WriteLine($"\n>> INTERNAL Request: User in Elevator {elevatorId} selected floor {destinationFloor}");
        Request request = new Request(destinationFloor, Direction.IDLE, RequestSource.INTERNAL);

        if (elevators.TryGetValue(elevatorId, out Elevator elevator))
        {
            elevator.AddRequest(request);
        }
        else
        {
            Console.Error.WriteLine("Invalid elevator ID.");
        }
    }

    public void Shutdown()
    {
        Console.WriteLine("Shutting down elevator system...");
        foreach (Elevator elevator in elevators.Values)
        {
            elevator.StopElevator();
        }
        Task.WaitAll(elevatorTasks.ToArray());
    }
}