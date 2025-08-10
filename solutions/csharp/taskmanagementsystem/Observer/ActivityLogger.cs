class ActivityLogger : ITaskObserver
{
    public void Update(Task task, string changeType)
    {
        Console.WriteLine($"LOGGER: Task '{task.GetTitle()}' was updated. Change: {changeType}");
    }
}