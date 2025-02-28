using System;

namespace TaskManagementSystem
{
    public class Task
    {
        public string Id { get; }
        public string Title { get; set; }
        public string Description { get; set; }
        public DateTime DueDate { get; set; }
        public int Priority { get; set; }
        public TaskStatus Status { get; set; }
        public User AssignedUser { get; }

        public Task(string id, string title, string description, DateTime dueDate, int priority, User assignedUser)
        {
            Id = id;
            Title = title;
            Description = description;
            DueDate = dueDate;
            Priority = priority;
            Status = TaskStatus.PENDING;
            AssignedUser = assignedUser;
        }

        public override bool Equals(object obj)
        {
            if (obj is Task task)
            {
                return Id == task.Id;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }
    }
}