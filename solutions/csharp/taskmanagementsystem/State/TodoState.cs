class TodoState : TaskState
{
    public override void StartProgress(Task task)
    {
        task.SetState(new InProgressState());
    }

    public override void CompleteTask(Task task)
    {
        Console.WriteLine("Cannot complete a task that is not in progress.");
    }

    public override void ReopenTask(Task task)
    {
        Console.WriteLine("Task is already in TO-DO state.");
    }

    public override TaskStatus GetStatus() => TaskStatus.TODO;
}