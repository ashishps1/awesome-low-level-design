class TaskList
{
    private readonly string id;
    private readonly string name;
    private readonly List<Task> tasks;
    private readonly object listLock = new object();

    public TaskList(string name)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.tasks = new List<Task>();
    }

    public void AddTask(Task task)
    {
        lock (listLock)
        {
            tasks.Add(task);
        }
    }

    public List<Task> GetTasks()
    {
        lock (listLock)
        {
            return new List<Task>(tasks); // Return copy
        }
    }

    public string GetId() => id;
    public string GetName() => name;

    public void Display()
    {
        Console.WriteLine($"--- Task List: {name} ---");
        foreach (var task in tasks)
        {
            task.Display("");
        }
        Console.WriteLine("-----------------------------------");
    }
}