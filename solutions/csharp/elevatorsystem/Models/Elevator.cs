class Elevator
{
    private readonly int id;
    private int currentFloor;
    private IElevatorState state;
    private volatile bool isRunning = true;

    private readonly SortedSet<int> upRequests;
    private readonly SortedSet<int> downRequests;
    private readonly object lockObject = new object();

    // Observer Pattern: List of observers
    private readonly List<IElevatorObserver> observers = new List<IElevatorObserver>();

    public Elevator(int id)
    {
        this.id = id;
        this.currentFloor = 1;
        this.upRequests = new SortedSet<int>();
        this.downRequests = new SortedSet<int>(Comparer<int>.Create((a, b) => b.CompareTo(a)));
        this.state = new IdleState();
    }

    // --- Observer Pattern Methods ---
    public void AddObserver(IElevatorObserver observer)
    {
        observers.Add(observer);
        observer.Update(this); // Send initial state
    }

    public void NotifyObservers()
    {
        foreach (IElevatorObserver observer in observers)
        {
            observer.Update(this);
        }
    }

    // --- State Pattern Methods ---
    public void SetState(IElevatorState state)
    {
        this.state = state;
        NotifyObservers(); // Notify observers on direction change
    }

    public void Move()
    {
        state.Move(this);
    }

    // --- Request Handling ---
    public void AddRequest(Request request)
    {
        lock (lockObject)
        {
            Console.WriteLine($"Elevator {id} processing: {request}");
            state.AddRequest(this, request);
        }
    }

    // --- Getters and Setters ---
    public int GetId() => id;
    
    public int GetCurrentFloor()
    {
        lock (lockObject)
        {
            return currentFloor;
        }
    }

    public void SetCurrentFloor(int floor)
    {
        lock (lockObject)
        {
            this.currentFloor = floor;
        }
        NotifyObservers(); // Notify observers on floor change
    }

    public Direction GetDirection() => state.GetDirection();
    public SortedSet<int> GetUpRequests() => upRequests;
    public SortedSet<int> GetDownRequests() => downRequests;
    public bool IsRunning() => isRunning;
    public void StopElevator() => isRunning = false;

    public void Run()
    {
        while (isRunning)
        {
            Move();
            try
            {
                Thread.Sleep(1000); // Simulate movement time
            }
            catch (ThreadInterruptedException)
            {
                isRunning = false;
            }
        }
    }
}