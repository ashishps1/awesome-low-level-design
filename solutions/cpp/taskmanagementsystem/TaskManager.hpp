#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <vector>
#include <string>
#include "Task.hpp"
#include "User.hpp"

class TaskManager {
private:
    std::vector<Task*> tasks;
    std::vector<User*> users;
    int taskIdCounter;
    int userIdCounter;

public:
    TaskManager();
    ~TaskManager();
    
    // User management
    User* registerUser(const std::string& username, const std::string& email);
    void removeUser(const std::string& userId);
    
    // Task management
    Task* createTask(const std::string& title, const std::string& description,
                    TaskPriority priority = TaskPriority::MEDIUM);
    void removeTask(const std::string& taskId);
    bool assignTask(const std::string& taskId, const std::string& userId);
    bool updateTaskStatus(const std::string& taskId, TaskStatus status);
    bool addTaskDependency(const std::string& taskId, const std::string& dependencyId);
    bool addTaskComment(const std::string& taskId, const std::string& comment);
    
    // Display functions
    void displayUserTasks(const std::string& userId) const;
    void displayAllTasks() const;
    void displayAllUsers() const;
    std::vector<Task*> getTasksByStatus(TaskStatus status) const;
    std::vector<Task*> getTasksByPriority(TaskPriority priority) const;

private:
    User* findUser(const std::string& userId) const;
    Task* findTask(const std::string& taskId) const;
    bool checkDependenciesMet(const Task* task) const;
    std::string generateTaskId();
    std::string generateUserId();
};

#endif 