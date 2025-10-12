class Task
{
    private readonly string id;
    private string title;
    private string description;
    private string dueDate;
    private TaskPriority priority;
    private readonly User createdBy;
    private User assignee;
    private TaskState currentState;
    private readonly HashSet<Tag> tags;
    private readonly List<Comment> comments;
    private readonly List<Task> subtasks;
    private readonly List<ActivityLog> activityLogs;
    private readonly List<ITaskObserver> observers;
    private readonly object taskLock = new object();

    public Task(TaskBuilder builder)
    {
        this.id = builder.Id;
        this.title = builder.Title;
        this.description = builder.Description;
        this.dueDate = builder.DueDate;
        this.priority = builder.Priority;
        this.createdBy = builder.CreatedBy;
        this.assignee = builder.Assignee;
        this.tags = builder.Tags;
        this.currentState = new TodoState(); // Initial state
        this.comments = new List<Comment>();
        this.subtasks = new List<Task>();
        this.activityLogs = new List<ActivityLog>();
        this.observers = new List<ITaskObserver>();
        AddLog($"Task created with title: {title}");
    }

    public void SetAssignee(User user)
    {
        lock (taskLock)
        {
            this.assignee = user;
            AddLog($"Assigned to {user.GetName()}");
            NotifyObservers("assignee");
        }
    }

    public void UpdatePriority(TaskPriority priority)
    {
        lock (taskLock)
        {
            this.priority = priority;
            NotifyObservers("priority");
        }
    }

    public void AddComment(Comment comment)
    {
        lock (taskLock)
        {
            comments.Add(comment);
            AddLog($"Comment added by {comment.GetAuthor().GetName()}");
            NotifyObservers("comment");
        }
    }

    public void AddSubtask(Task subtask)
    {
        lock (taskLock)
        {
            subtasks.Add(subtask);
            AddLog($"Subtask added: {subtask.GetTitle()}");
            NotifyObservers("subtask_added");
        }
    }

    // State Pattern Methods
    public void SetState(TaskState state)
    {
        this.currentState = state;
        AddLog($"Status changed to: {state.GetStatus()}");
        NotifyObservers("status");
    }

    public void StartProgress() => currentState.StartProgress(this);
    public void CompleteTask() => currentState.CompleteTask(this);
    public void ReopenTask() => currentState.ReopenTask(this);

    // Observer Pattern Methods
    public void AddObserver(ITaskObserver observer) => observers.Add(observer);
    public void RemoveObserver(ITaskObserver observer) => observers.Remove(observer);

    public void NotifyObservers(string changeType)
    {
        foreach (var observer in observers)
        {
            observer.Update(this, changeType);
        }
    }

    public void AddLog(string logDescription)
    {
        activityLogs.Add(new ActivityLog(logDescription));
    }

    public bool IsComposite() => subtasks.Count > 0;

    public void Display(string indent = "")
    {
        Console.WriteLine($"{indent}- {title} [{GetStatus()}, {priority}, Due: {dueDate}]");
        if (IsComposite())
        {
            foreach (var subtask in subtasks)
            {
                subtask.Display(indent + "  ");
            }
        }
    }

    // Getters
    public string GetId() => id;
    public string GetTitle() => title;
    public string GetDescription() => description;
    public TaskPriority GetPriority() => priority;
    public string GetDueDate() => dueDate;
    public User GetAssignee() => assignee;
    public TaskStatus GetStatus() => currentState.GetStatus();

    public void SetTitle(string title) => this.title = title;
    public void SetDescription(string description) => this.description = description;
}

// Builder Pattern
class TaskBuilder
{
    public string Id { get; private set; }
    public string Title { get; private set; }
    public string Description { get; private set; } = "";
    public string DueDate { get; private set; }
    public TaskPriority Priority { get; private set; }
    public User CreatedBy { get; private set; }
    public User Assignee { get; private set; }
    public HashSet<Tag> Tags { get; private set; } = new HashSet<Tag>();

    public TaskBuilder(string title)
    {
        this.Id = Guid.NewGuid().ToString();
        this.Title = title;
    }

    public TaskBuilder SetDescription(string description)
    {
        this.Description = description;
        return this;
    }

    public TaskBuilder SetDueDate(string dueDate)
    {
        this.DueDate = dueDate;
        return this;
    }

    public TaskBuilder SetPriority(TaskPriority priority)
    {
        this.Priority = priority;
        return this;
    }

    public TaskBuilder SetAssignee(User assignee)
    {
        this.Assignee = assignee;
        return this;
    }

    public TaskBuilder SetCreatedBy(User createdBy)
    {
        this.CreatedBy = createdBy;
        return this;
    }

    public TaskBuilder SetTags(HashSet<Tag> tags)
    {
        this.Tags = tags;
        return this;
    }

    public Task Build()
    {
        return new Task(this);
    }
}