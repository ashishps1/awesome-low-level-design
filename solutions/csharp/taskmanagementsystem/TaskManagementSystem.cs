class TaskManagementSystem
{
    private static TaskManagementSystem instance;
    private static readonly object lockObject = new object();
    private readonly Dictionary<string, User> users = new Dictionary<string, User>();
    private readonly Dictionary<string, Task> tasks = new Dictionary<string, Task>();
    private readonly Dictionary<string, TaskList> taskLists = new Dictionary<string, TaskList>();

    private TaskManagementSystem() { }

    public static TaskManagementSystem GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new TaskManagementSystem();
                }
            }
        }
        return instance;
    }

    public User CreateUser(string name, string email)
    {
        User user = new User(name, email);
        users[user.GetId()] = user;
        return user;
    }

    public TaskList CreateTaskList(string listName)
    {
        TaskList taskList = new TaskList(listName);
        taskLists[taskList.GetId()] = taskList;
        return taskList;
    }

    public Task CreateTask(string title, string description, string dueDate,
                          TaskPriority priority, string createdByUserId)
    {
        if (!users.TryGetValue(createdByUserId, out User createdBy))
        {
            throw new ArgumentException("User not found.");
        }

        Task task = new TaskBuilder(title)
                .SetDescription(description)
                .SetDueDate(dueDate)
                .SetPriority(priority)
                .SetCreatedBy(createdBy)
                .Build();

        task.AddObserver(new ActivityLogger());

        tasks[task.GetId()] = task;
        return task;
    }

    public List<Task> ListTasksByUser(string userId)
    {
        if (!users.TryGetValue(userId, out User user))
        {
            return new List<Task>();
        }

        return tasks.Values.Where(task => task.GetAssignee() == user).ToList();
    }

    public List<Task> ListTasksByStatus(TaskStatus status)
    {
        return tasks.Values.Where(task => task.GetStatus() == status).ToList();
    }

    public void DeleteTask(string taskId)
    {
        tasks.Remove(taskId);
    }

    public List<Task> SearchTasks(string keyword, TaskSortStrategy sortingStrategy)
    {
        List<Task> matchingTasks = new List<Task>();
        foreach (var task in tasks.Values)
        {
            if (task.GetTitle().Contains(keyword) || task.GetDescription().Contains(keyword))
            {
                matchingTasks.Add(task);
            }
        }
        sortingStrategy.Sort(matchingTasks);
        return matchingTasks;
    }
}