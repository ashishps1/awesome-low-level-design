#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <fstream>
#include "TaskManager.h"
using namespace std;

class TaskManager
{
private:
    unordered_map<int, Task> tasks;
    vector<User> users;
    mutable mutex taskMutex;
    mutable mutex userMutex;

public:
    // create task method
    void TaskManager::createTask(const Task &task)
    {
        lock_guard<mutex> lock(taskMutex);
        if (tasks.find(task.getId()) == tasks.end())
        {
            cout << "Task with ID " << task.getId() << " already exists!" << endl;
            return;
        }
        tasks[task.getId()] = task;
        cout << "Task created successfully" << endl;
    }

    // update task method
    void TaskManager::updateTask(int taskId, const Task &updatedTask)
    {
        lock_guard<mutex> lock(taskMutex);
        if (tasks.find(taskId) == tasks.end())
        {
            cout << "Task with ID " << taskId << " does not exist!" << endl;
        }
        else
        {
            tasks[taskId] = updatedTask;
            cout << "Task updated successfully" << endl;
        }
    }

    // delete task method
    void TaskManager::deleteTask(int deleteTaskId)
    {
        if (tasks.find(deleteTaskId) == tasks.end())
        {
            cout << "Task with ID " << deleteTaskId << " does not exist!" << endl;
        }
        else
        {
            tasks.erase(deleteTaskId);
            cout << "Task deleted successfully" << endl;
        }
    }

    // search task on the basis of ID
    Task* TaskManager::searchTask(int taskId)
    {
        if (tasks.find(taskId) == tasks.end())
        {
            cout << "Task with ID " << taskId << " does not exist!" << endl;
            return nullptr;
        }
        else
        {
            return &tasks[taskId];
        }
    }

    // filtering task method
    vector<Task> TaskManager::filterTasks(const string &criteria, const string &value)
    {
        vector<Task> filteredTasks;
        for (const auto &pair : tasks)
        {
            const Task &task = pair.second;
            if ((criteria == "priority" && to_string(task.getPriority()) == value) ||
                (criteria == "status" && to_string(task.getStatus()) == value) ||
                (criteria == "assignedUser" && to_string(task.getAssignedUser()) == value)
            )
            {
                filteredTasks.push_back(task);
            }
        }
        return filteredTasks;
    }

    // mark task completed
    void TaskManager::markTaskComplete(int taskId)
    {
        if (tasks.find(taskId) == tasks.end())
        {
            cout << "Task with ID " << taskId << " does not exist!" << endl;
        }
        else
        {
            tasks[taskId].setStatus(COMPLETED);
            cout << "Task with ID " << taskId << " marked as completed!" << endl;
        }
    }

    // assign task to user
    void TaskManager::assignTaskToUser(int userID, int taskId)
    {
        // Check if user exists
        auto userIt = find_if(users.begin(), users.end(), [userID](const User &user)
                              { return user.getId() == userID; });

        if (userIt == users.end())
        {
            cout << "User with ID " << userID << " does not exist!" << endl;
            return;
        }

        if (tasks.find(taskId) == tasks.end())
        {
            cout << "Task with ID " << taskId << " does not exist!" << endl;
        }
        else
        {
            tasks[taskId].setAssignedUserId(userID);
            cout << "Task with ID " << taskId << " assigned to user " << userIt->getName() << "!" << endl;
        }
    }

    // Retrieving task history
    vector<Task> TaskManager::getTaskHistory()
    {
        vector<Task> completedTasks;
        for (const auto &pair : tasks)
        {
            const Task &task = pair.second;
            if (task.getStatus() == COMPLETED)
            {
                completedTasks.push_back(task);
            }
        }
        return completedTasks;
    }

    void TaskManager::addUser(const User &user)
    {
        lock_guard<mutex> lock(userMutex);
        for (const auto &existingUsers : users)
        {
            if (existingUsers.getId() == user.getId())
            {
                cout << "User with ID " << user.getId() << " already exists!" << endl;
                return;
            }
        }
        users.push_back(user);
        cout << "User added successfully!" << endl;
    }

    void TaskManager::deleteUser(int userId)
    {
        lock_guard<mutex> lock(userMutex);
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->getId() == userId)
            {
                users.erase(it);
                cout << "User with ID " << userId << " deleted successfully!" << endl;
                return;
            }
        }
        cout << "User with ID " << userId << " not found!" << endl;
    }

    void saveTasksToFile(const string &filename)
    {
        lock_guard<mutex> lock(taskMutex);
        ofstream outFile(filename);
        if (!outFile)
        {
            cout << "Error opening file for saving tasks!" << endl;
            return;
        }
        for (const auto &pair : tasks)
        {
            const Task &task = pair.second;
            outFile << task.getId() << "," << task.getTitle() << "," << task.getDescription()
                    << "," << task.getDueDate() << "," << task.getPriority()
                    << "," << task.getStatus() << "," << task.getAssignedUser() << endl;
        }
        outFile.close();
        cout << "Tasks saved to file successfully!" << endl;
    }
};