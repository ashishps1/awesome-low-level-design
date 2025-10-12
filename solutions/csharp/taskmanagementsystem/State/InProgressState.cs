class InProgressState : TaskState
{
    public override void StartProgress(Task task)
    {
        Console.WriteLine("Task is already in progress.");
    }

    public override void CompleteTask(Task task)
    {
        task.SetState(new DoneState());
    }

    public override void ReopenTask(Task task)
    {
        task.SetState(new TodoState());
    }

    public override TaskStatus GetStatus() => TaskStatus.IN_PROGRESS;
}