using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace TaskManagementSystem
{
    public class TaskManager
    {
        private static TaskManager _instance;
        private readonly ConcurrentDictionary<string, Task> _tasks;
        private readonly ConcurrentDictionary<string, List<Task>> _userTasks;

        private TaskManager()
        {
            _tasks = new ConcurrentDictionary<string, Task>();
            _userTasks = new ConcurrentDictionary<string, List<Task>>();
        }

        public static TaskManager GetInstance()
        {
            if (_instance == null)
            {
                _instance = new TaskManager();
            }
            return _instance;
        }

        public void CreateTask(Task task)
        {
            _tasks[task.Id] = task;
            AssignTaskToUser(task.AssignedUser, task);
        }

        public void UpdateTask(Task updatedTask)
        {
            if (_tasks.TryGetValue(updatedTask.Id, out Task existingTask))
            {
                lock (existingTask)
                {
                    existingTask.Title = updatedTask.Title;
                    existingTask.Description = updatedTask.Description;
                    existingTask.DueDate = updatedTask.DueDate;
                    existingTask.Priority = updatedTask.Priority;
                    existingTask.Status = updatedTask.Status;

                    if (!existingTask.AssignedUser.Equals(updatedTask.AssignedUser))
                    {
                        UnassignTaskFromUser(existingTask.AssignedUser, existingTask);
                        AssignTaskToUser(updatedTask.AssignedUser, existingTask);
                    }
                }
            }
        }

        public void DeleteTask(string taskId)
        {
            if (_tasks.TryRemove(taskId, out Task task))
            {
                UnassignTaskFromUser(task.AssignedUser, task);
            }
        }

        public List<Task> SearchTasks(string keyword)
        {
            return _tasks.Values
                         .Where(task => task.Title.Contains(keyword, StringComparison.OrdinalIgnoreCase) || 
                                        task.Description.Contains(keyword, StringComparison.OrdinalIgnoreCase))
                         .ToList();
        }

        public List<Task> FilterTasks(TaskStatus status, DateTime startDate, DateTime endDate, int priority)
        {
            return _tasks.Values
                         .Where(task => task.Status == status && task.DueDate >= startDate && task.DueDate <= endDate && task.Priority == priority)
                         .ToList();
        }

        public void MarkTaskAsCompleted(string taskId)
        {
            if (_tasks.TryGetValue(taskId, out Task task))
            {
                lock (task)
                {
                    task.Status = TaskStatus.COMPLETED;
                }
            }
        }

        public List<Task> GetTaskHistory(User user)
        {
            return _userTasks.GetOrAdd(user.Id, new List<Task>());
        }

        private void AssignTaskToUser(User user, Task task)
        {
            _userTasks.GetOrAdd(user.Id, new List<Task>()).Add(task);
        }

        private void UnassignTaskFromUser(User user, Task task)
        {
            if (_userTasks.TryGetValue(user.Id, out List<Task> tasks))
            {
                tasks.Remove(task);
            }
        }
    }
}