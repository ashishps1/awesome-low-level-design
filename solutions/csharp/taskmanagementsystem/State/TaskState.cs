abstract class TaskState
{
    public abstract void StartProgress(Task task);
    public abstract void CompleteTask(Task task);
    public abstract void ReopenTask(Task task);
    public abstract TaskStatus GetStatus();
}