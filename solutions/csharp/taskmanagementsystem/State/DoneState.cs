class DoneState : TaskState
{
    public override void StartProgress(Task task)
    {
        Console.WriteLine("Cannot start a completed task. Reopen it first.");
    }

    public override void CompleteTask(Task task)
    {
        Console.WriteLine("Task is already done.");
    }

    public override void ReopenTask(Task task)
    {
        task.SetState(new TodoState());
    }

    public override TaskStatus GetStatus() => TaskStatus.DONE;
}