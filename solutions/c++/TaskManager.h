#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include "User.h"
#include <unordered_map>
#include <vector>
#include <mutex>

class TaskManager
{
private:
    unordered_map<int, Task> tasks;
    vector<User> users;
    mutable mutex taskMutex;
    mutable mutex userMutex;

public:

// TaskManager methods
    void createTask(const Task &task);
    void updateTask(int taskId, const Task &updatedTask);
    void deleteTask(int deleteTaskId);
    Task *searchTask(int taskId);
    vector<Task> filterTasks(const string &criteria, const string &value);
    void markTaskComplete(int taskId);
    void assignTaskToUser(int userID, int taskId);
    vector<Task> getTaskHistory();

// User methods
    void addUser(const User &user);
    void deleteUser(int userId);

    void saveTasksToFile(const string &filename);
};

#endif
