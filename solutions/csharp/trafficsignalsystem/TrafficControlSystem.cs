class TrafficControlSystem
{
    private static TrafficControlSystem instance;
    private static readonly object lockObject = new object();
    private readonly List<IntersectionController> intersections = new List<IntersectionController>();
    private readonly List<Task> tasks = new List<Task>();

    private TrafficControlSystem() { }

    public static TrafficControlSystem GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new TrafficControlSystem();
                }
            }
        }
        return instance;
    }

    public void AddIntersection(int intersectionId, int greenDuration, int yellowDuration)
    {
        IntersectionController intersection = new IntersectionControllerBuilder(intersectionId)
                .WithDurations(greenDuration, yellowDuration)
                .AddObserver(new CentralMonitor())
                .Build();
        intersections.Add(intersection);
    }

    public void StartSystem()
    {
        if (intersections.Count == 0)
        {
            Console.WriteLine("No intersections to manage. System not starting.");
            return;
        }

        Console.WriteLine("--- Starting Traffic Control System ---");

        foreach (var intersection in intersections)
        {
            Task task = Task.Run(() => intersection.Run());
            tasks.Add(task);
        }
    }

    public void StopSystem()
    {
        Console.WriteLine("\n--- Shutting Down Traffic Control System ---");

        foreach (var intersection in intersections)
        {
            intersection.Stop();
        }

        Task.WaitAll(tasks.ToArray(), TimeSpan.FromSeconds(5));

        Console.WriteLine("All intersections stopped. System shut down.");
    }
}